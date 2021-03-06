#include "include/client.hpp"
#include <cstring>

Client::Client(const char *name)
{
    size_t len = strlen(name);
    if (len <= 30)
    {
        strcpy(nickname, name);
    }
    else
    {
        throw "NAME MUST BE <= 30 SYMBOLS";
    }
}

Client::~Client()
{
    /* TODO send to server that user is offline */
    this->send_data("I'm offline", 12, 0);
    close(sock);
}

/*
* <s>: socket
* <buf>: message
* <len>: length of message,
* <flags>: flags to send (default=0)
* returns: if bad: -1 else: count of sended bytes
*/
int Client::send_data(const char *buf, int len, int flags /*=0*/)
{
    int total = 0;
    int n;

    while (total < len)
    {
        n = send(sock, buf + total, len - total, flags);
        if (n == -1)
            break;
        total += n;
    }

    return (n == -1 ? -1 : total);
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
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("SOCKET CONNECT ERROR");
        exit(CONNECTION_ERROR);
    }
    std::cout << "Connected successfull...\n";
    std::thread listen_thread([&](){listen_server();});
    listen_thread.detach();
    return true;
}

void Client::listen_server()
{
    std::cout << "listening server for data...\n";
    while (true)
    {
        char data[BUF_SIZE];
        recv(sock, data, BUF_SIZE, 0);
        std::cout << data;
    }
}
