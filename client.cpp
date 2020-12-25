#include "include/client.hpp"
#include <cstring>

Client::Client(const char* name)
{
    size_t len = strlen(name);
    if (len <= 30) { strcpy(nickname, name); }
    else { throw "NAME MUST BE <= 30 SYMBOLS"; }
}

Client::~Client() { /* TODO send to server that user is offline */ }

// returns true on success, else false
bool Client::send_data(const char* data)
{
    if (send(sock, data, BUF_SIZE, 0) != -1)
        return true;
    return false;
}

bool Client::cconnect(in_addr_t __addr, in_port_t __port)
{
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket error.");
        exit(CREATE_ERROR);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(__port);
    addr.sin_addr.s_addr = htonl(__addr);
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("SOCKET CONNECT ERROR");
        exit(CONNECTION_ERROR);
    }
    std::cout << "Connected successfull...\n";
    return true;
}

void Client::listen_server()
{
    while (true)
    {
        char data[BUF_SIZE];
        recv(sock, data, BUF_SIZE, 0);
        std::cout << data;
    }
}