#pragma once

#include "library.hpp"

class Client
{
private:
    int sock;                // server socket
    struct sockaddr_in addr; // server address
    char nickname[15];       // nickname

public:
    explicit Client(const char *name);                         // Constructor
    ~Client();                                                 // Destructor
    int send_data(const char *buf, int len, int flags /*=0*/); // if success: return len, else -1
    void listen_server();                                      // listen cconected server (inf loop)
    bool cconnect(in_addr_t __addr, in_port_t __port);         // Connect client to ADDR with port PORT
};
