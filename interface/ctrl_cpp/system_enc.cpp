#include "./controller_enc.h"
#include "../../cpp/tcp_protocol_client.h"

#include <iostream>
#include <string>
#include <chrono>

#include "seal/seal.h"
#include <vector>
using namespace seal;
using namespace std;

using namespace std;

const string host = "127.0.0.1";
const int port = 9999;

const double pq[4][3] = {{-13.3443203999253, 15.0030518107562, -0.0227503562486410},
                        {69.7255986973738, -81.7399354434618, 0.145231734991849},
                        {-107.639518675920, 147.752435602488, -0.505904999998477},
                        {51.6633130000854, -88.1602769609419, 0.492475989578353}};

int64_t pq_q[4][3] = {{0}};

const double r = 1000, s = 1000;

inline void print_parameters(const seal::SEALContext &context);

int main()
{
    EncryptionParameters parms(scheme_type::bgv);
    size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, {42, 42, 42}));
    parms.set_plain_modulus(PlainModulus::Batching(poly_modulus_degree, 24));

    SEALContext context(parms);

    print_parameters(context);

    KeyGenerator keygen(context); 
    SecretKey secret_key = keygen.secret_key();

    PublicKey public_key;
    keygen.create_public_key(public_key);

    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);

    vector<int> steps = {1, 2};
    GaloisKeys galois_keys;
    keygen.create_galois_keys(steps, galois_keys);

    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

    BatchEncoder batch_encoder(context);
    size_t slot_count = batch_encoder.slot_count();

    // quantize matrix
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            pq_q[i][j] = (int64_t)(pq[i][j] * s);
        }
    }

    vector<int64_t> pod_matrix(slot_count, 0ULL);
    vector<Ciphertext> pq_enc(4);
    vector<Ciphertext> io_enc(4);
    Plaintext plain;
    Ciphertext cipher;
    for(int i = 0; i < 4; i++)
    {
        pod_matrix[0] = pq_q[i][0];
        pod_matrix[1] = pq_q[i][1];
        pod_matrix[2] = pq_q[i][2];
        
        batch_encoder.encode(pod_matrix, plain);
        encryptor.encrypt(plain, cipher);
        pq_enc[i] = cipher;
    }
    for(int i = 0; i < 4; i++)
    {
        pod_matrix[0] = 0;
        pod_matrix[1] = 0;
        pod_matrix[2] = 0;
        
        batch_encoder.encode(pod_matrix, plain);
        encryptor.encrypt(plain, cipher);
        io_enc[i] = cipher;
    }

    controller_encrypted ctrl_enc = controller_encrypted(context, relin_keys, galois_keys);
    
    ctrl_enc.set_pq(pq_enc);
    ctrl_enc.set_io(io_enc);

    Ciphertext u_c;
    Plaintext u_p;
    vector<int64_t> u_d;

    double sample_time = 20;
    double conn_margin = 0.25;
    int state = 1;
    double y0 = 0;
    double y1 = 0;
    double u = 0;
    auto stc = chrono::high_resolution_clock::now();
    auto edc = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(edc - stc);
    double run_time;
    bool EoL = true;

    Plaintext sampled_data_p;
    Ciphertext sampled_data_c;

    tcp_client tccp = tcp_client(host, port);
    string flag;

    while(EoL)
    {
        if(state == 1)
        {
            flag = tccp.Recv<string>();
            
            if(flag == "R")
            {
                tccp.Send<string>("g_y");

                stc = chrono::high_resolution_clock::now();

                y0 = tccp.Recv<double>();
                y1 = tccp.Recv<double>();
                // u = ctrl_obj.ctrl(y0, y1);

                pod_matrix[0] = (int64_t)(y0 * r);
                pod_matrix[1] = (int64_t)(y1 * r);
                pod_matrix[2] = (int64_t)(u * r);

                batch_encoder.encode(pod_matrix, sampled_data_p);
                encryptor.encrypt(sampled_data_p, sampled_data_c);

                ctrl_enc.mem_update(sampled_data_c);
                
                u_c = ctrl_enc.ctrl();

                decryptor.decrypt(u_c, u_p);
                batch_encoder.decode(u_p, u_d);
                u = u_d[0] / r / s;
        
                cout << "y0: " << y0 <<" | y1: " << y1 << " | u: " << u << endl;

                state = 2;
            }
            else if(flag == "E")
            {
                EoL = false;
            }
            else
            {
                exit(-1);
            }
        }
        else if(state == 2)
        {
            while(true)
            {
                flag = tccp.Recv<string>();

                if(flag == "R")
                {
                    edc = chrono::high_resolution_clock::now();
                    duration = chrono::duration_cast<chrono::nanoseconds>(edc - stc);
                    run_time = duration.count() / 1000000;
                    
                    if(run_time < (sample_time - conn_margin))
                    {
                        tccp.Send<string>("w");
                    }
                    else
                    {
                        tccp.Send<string>("s_u");
                        tccp.Send<double>(u);
                        cout << "sample_period: " << run_time << "ms" << endl;
                        state = 1;
                        break;
                    }
                }
                else if(flag == "E")
                {
                    EoL = false;
                    break;
                }
                else
                {
                    exit(-1);
                }
            }
        }
        else
        {
            exit(-1);
        }
    }
    
    return 0;
}

inline void print_parameters(const seal::SEALContext &context)
{
    auto &context_data = *context.key_context_data();

    /*
    Which scheme are we using?
    */
    std::string scheme_name;
    switch (context_data.parms().scheme())
    {
    case seal::scheme_type::bfv:
        scheme_name = "BFV";
        break;
    case seal::scheme_type::ckks:
        scheme_name = "CKKS";
        break;
    case seal::scheme_type::bgv:
        scheme_name = "BGV";
        break;
    default:
        throw std::invalid_argument("unsupported scheme");
    }
    std::cout << "/" << std::endl;
    std::cout << "| Encryption parameters :" << std::endl;
    std::cout << "|   scheme: " << scheme_name << std::endl;
    std::cout << "|   poly_modulus_degree: " << context_data.parms().poly_modulus_degree() << std::endl;

    /*
    Print the size of the true (product) coefficient modulus.
    */
    std::cout << "|   coeff_modulus size: ";
    std::cout << context_data.total_coeff_modulus_bit_count() << " (";
    auto coeff_modulus = context_data.parms().coeff_modulus();
    std::size_t coeff_modulus_size = coeff_modulus.size();
    for (std::size_t i = 0; i < coeff_modulus_size - 1; i++)
    {
        std::cout << coeff_modulus[i].bit_count() << " + ";
    }
    std::cout << coeff_modulus.back().bit_count();
    std::cout << ") bits" << std::endl;

    /*
    For the BFV scheme print the plain_modulus parameter.
    */
    if (context_data.parms().scheme() == seal::scheme_type::bfv)
    {
        std::cout << "|   plain_modulus: " << context_data.parms().plain_modulus().value() << std::endl;
    }

    std::cout << "\\" << std::endl;
}
