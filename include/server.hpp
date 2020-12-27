#pragma once

#include "library.hpp"

class Server
{
private:
    std::vector<int> users;
    int sock, listener;
    struct sockaddr_in addr;

public:
    Server(in_addr_t __addr, in_port_t __port);
    ~Server();
    bool setup();
    void listen_user(int socket);
    bool send_data(int socket, const char *data);
    void send_all(const char *data);
    void start();
};
