#ifndef TPC_H
#define TPC_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class tcp_client
{
    private:
        sockaddr_in client;

        string addr = "localhost";
        int port = 9999;

        int byte_size = 1024;

        int socket_instance ;

    public:
        tcp_client(string host, int port)
        {
            this->addr = host;
            this->port = port;

            this->client.sin_family = AF_INET;
            this->client.sin_addr.s_addr = inet_addr(host.c_str());
            this->client.sin_port = htons(port);

            int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if(client_socket == -1)
            {
                cout << "def: _construct | error | socket create false" << endl;
                exit(-1);
            }
            else
            {
                this->socket_instance = client_socket;
            }

            setsockopt(this->socket_instance, IPPROTO_TCP, TCP_NODELAY, (const char*)1, sizeof(1));

            int err = connect(this->socket_instance, (sockaddr*)&this->client, sizeof(this->client));
            if(err == -1)
            {
                cout << "def: _construct | error | tcp connect false" << endl;
                exit(-1);
            }
        };

        ~tcp_client()
        {
            close(this->socket_instance);
            cout << "def: _destruct | alert | close client" << endl;
        };

        void set_byte(int byte)
        {
            this->byte_size = byte;
        };

        template <typename T>
        void Send(T data)
        {
            if constexpr (is_same_v<T, int>)
            {
                stringstream data_stearm;
                data_stearm << "<INT>" << data << "<END>";
                string send_data = data_stearm.str();

                int err = send(this->socket_instance, send_data.data(), send_data.length(), 0);
                if(err == -1)
                {
                    cout << "def: send | error | communication false" << endl;
                    exit(-1);
                }

                vector<char> buffer(this->byte_size);
                string read_data;
                int byte_read;
                while(true)
                {
                    byte_read = read(this->socket_instance, buffer.data(), buffer.size());
                    if (byte_read <= 0)
                    {
                        cout <<"def: send | error | communication false" << endl;
                        exit(-1);
                    }

                    read_data.append(buffer.data(), byte_read);

                    if(read_data.find("<END>") != string::npos)
                    {
                        read_data.erase(read_data.find("<END>"), read_data.find("<END>") + 5);
                        break;
                    }
                }

                if (read_data.find("<CHK>") != string::npos)
                {
                    cout << "def: send | alert | communication complete" << endl;
                }
                else
                {
                    cout << "def: send | error | communication false" << endl;
                    exit(-1);
                }
            }
            else if constexpr (is_same_v<T, double>)
            {
                stringstream data_stearm;
                data_stearm << "<FLOAT>" << data << "<END>";
                string send_data = data_stearm.str();

                int err = send(this->socket_instance, send_data.data(), send_data.length(), 0);
                if(err == -1)
                {
                    cout << "def: send | error | communication false" << endl;
                    exit(-1);
                }

                vector<char> buffer(this->byte_size);
                string read_data;
                int byte_read;
                while(true)
                {
                    byte_read = read(this->socket_instance, buffer.data(), buffer.size());
                    if (byte_read <= 0)
                    {
                        cout <<"def: send | error | communication false" << endl;
                        exit(-1);
                    }

                    read_data.append(buffer.data(), byte_read);

                    if(read_data.find("<END>") != string::npos)
                    {
                        read_data.erase(read_data.find("<END>"), read_data.find("<END>") + 5);
                        break;
                    }
                }

                if (read_data.find("<CHK>") != string::npos)
                {
                    cout << "def: send | alert | communication complete" << endl;
                }
                else
                {
                    cout << "def: send | error | communication false" << endl;
                    exit(-1);
                }
            }
            else if constexpr (is_same_v<T, string>)
            {
                stringstream data_stearm;
                data_stearm << "<STR>" << data << "<END>";
                string send_data = data_stearm.str();

                int err = send(this->socket_instance, send_data.data(), send_data.length(), 0);
                if(err == -1)
                {
                    cout << "def: send | error | communication false" << endl;
                    exit(-1);
                }

                vector<char> buffer(this->byte_size);
                string read_data;
                int byte_read;
                while(true)
                {
                    byte_read = read(this->socket_instance, buffer.data(), buffer.size());
                    if (byte_read <= 0)
                    {
                        cout <<"def: send | error | communication false" << endl;
                        exit(-1);
                    }

                    read_data.append(buffer.data(), byte_read);

                    if(read_data.find("<END>") != string::npos)
                    {
                        read_data.erase(read_data.find("<END>"), read_data.find("<END>") + 5);
                        break;
                    }
                }

                if (read_data.find("<CHK>") != string::npos)
                {
                    cout << "def: send | alert | communication complete" << endl;
                }
                else
                {
                    cout << "def: send | error | communication false" << endl;
                    exit(-1);
                }
            }
            else 
            {
                cout << "def: send | error | type false" << endl;
                exit(-1);
            }
        };

        template <typename T>
        T Recv()
        {
            string send_data = "<RED><END>";

            int err = send(this->socket_instance, send_data.data(), send_data.length(), 0);
            if(err == -1)
            {
                cout << "def: send | error | communication false" << endl;
                exit(-1);
            }

            vector<char> buffer(this->byte_size);
            string read_data;
            int byte_read;
            while(true)
            {
                byte_read = read(this->socket_instance, buffer.data(), buffer.size());
                if (byte_read <= 0)
                {
                    cout <<"def: send | error | communication false" << endl;
                }

                read_data.append(buffer.data(), byte_read);

                if(read_data.find("<END>") != string::npos)
                {
                    read_data.erase(read_data.find("<END>"), read_data.find("<END>") + 5);
                    break;
                }
            }

            T return_value;
            if(read_data.find("<INT>") != string::npos)
            {
                read_data.erase(read_data.find("<INT>"), read_data.find("<INT>") + 5);
                return_value = stoi(read_data);
            }
            else if(read_data.find("<FLOAT>") != string::npos)
            {
                read_data.erase(read_data.find("<FLOAT>"), read_data.find("<FLOAT>") + 7);
                return_value = stod(read_data);
            }
            else if(read_data.find("<STR>") != string::npos)
            {
                read_data.erase(read_data.find("<STR>"), read_data.find("<STR>") + 5);
                return_value = read_data;
            }
            else
            {
                cout << "def: recv | error | type false" << endl;
                exit(-1);
            }

            return return_value;
        }
};

#endif