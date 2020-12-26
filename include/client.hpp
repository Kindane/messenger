#pragma once

#include "library.hpp"

class Client
{
private:
    int sock; // server socket
    struct sockaddr_in addr; // server address
    char nickname[15];
public:
    explicit Client(const char* name);
    ~Client();
    bool send_data(const char* data);
    void listen_server();
    bool cconnect(in_addr_t __addr, in_port_t __port);
};
