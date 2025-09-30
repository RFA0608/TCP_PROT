#include "./controller.h"
#include "../../cpp/tcp_protocol_client.h"

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

const string host = "127.0.0.1";
const int port = 9999;

int main()
{
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
    
    controller ctrl_obj = controller();
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
                u = ctrl_obj.ctrl(y0, y1);

                cout << "y0: " << y0 <<" | y1: " << y1 << endl;

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