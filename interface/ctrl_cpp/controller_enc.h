#include "seal/seal.h"
#include <vector>
using namespace seal;
using namespace std;

class controller_encrypted
{
    private:
        SEALContext ctext;

        Evaluator evaluator;

        RelinKeys relin_keys;

        GaloisKeys galois_keys;

        vector<Ciphertext>pq;

        vector<Ciphertext>io; // oldest -> newest

    public:
        controller_encrypted(SEALContext& context, RelinKeys relin_keys, GaloisKeys galois_keys): ctext(context), evaluator(context), pq(4), io(4) 
        {
            this->relin_keys = relin_keys;
            this->galois_keys = galois_keys;
        };
        ~controller_encrypted(){};

        void set_pq(vector<Ciphertext>& pq)
        {
            for(int i = 0; i < 4; i++)
            {
                this->pq[i] = pq[i];
            }
        }

        void set_io(vector<Ciphertext>& io)
        {
            for(int i = 0; i < 4; i++)
            {
                this->io[i] = io[i];
            }
        }

        void mem_update(Ciphertext new_one)
        {
            io.erase(io.begin());
            io.push_back(new_one);
        };

        Ciphertext ctrl()
        {
            vector<Ciphertext> r_mul(4);
            Ciphertext t_mul;
            Ciphertext r_sum;
            Ciphertext u_enc;

            for(int i = 0; i < 4; i++)
            {
                this->evaluator.multiply(this->pq[i], this->io[i], t_mul);
                this->evaluator.relinearize_inplace(t_mul, this->relin_keys);
                r_mul[i] = t_mul;
            }

            r_sum = r_mul[0];

            for(int i = 1; i < 4; i++)
            {
                this->evaluator.add_inplace(r_sum, r_mul[i]);
            }

            u_enc = r_sum;
            this->evaluator.rotate_rows_inplace(r_sum, 1, this->galois_keys);
            this->evaluator.add_inplace(u_enc, r_sum);
            this->evaluator.rotate_rows_inplace(r_sum, 1, this->galois_keys);
            this->evaluator.add_inplace(u_enc, r_sum);

            return u_enc;
        };
};