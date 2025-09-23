#include "tcp_protocol_client.h"
#include <string>
#include <iostream>
using namespace std;

const string host = "127.0.0.1";
const int port = 9999;

int main()
{
    tcp_client tccp = tcp_client(host, port);
    for(int i = 0; i < 10; i++)
    {
        int k = tccp.Recv<int>();
        cout << k << endl;

        tccp.Send<int>(i);
    }
    
}