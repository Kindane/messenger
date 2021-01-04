#pragma once

#include "library.hpp"

class Server
{
private:
    std::vector<int*> users;  // users sockers
    int sock, listener;      // server sockets
    struct sockaddr_in addr; // server address

public:
    Server(in_addr_t __addr, in_port_t __port);                // addr = address, port = port
    ~Server();                                                 // Destructor
    bool setup(int connections);                               // bind && getting ready for accept users...
    void listen_user(int socket);                              // listen user (inf loop)
    int send_data(int s, const char *buf, int len, int flags); // send data to socket
    void send_all(const char *data);                           // send data to all user
    void start();                                              // LOGIC ERROR!! (must be inf loop)
};
