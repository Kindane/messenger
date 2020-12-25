#include "include/server.hpp"

//ctor
Server::Server(in_addr_t __addr, in_port_t __port)
{
    addr.sin_port = htons(__port);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(__addr);

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        perror("CANNOT CREATE A SERVER SOCKET");
        exit(CREATE_ERROR);
    }
}

//dtor
Server::~Server() { send_all("\n\nBAD CONNECTION WITH SERVER...\n\n"); }

bool Server::setup()
{
    std::cout << "setup\n";
    if (bind(listener, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("CANNOT BIND SOCKET");
        exit(BIND_ERROR);
    }
    else
    {
        listen(listener, 1);
        return true;
    }
}

// listen user (inf loop)
void Server::listen_user(int socket)
{
    // users.push_back(socket);
    while (true)
    {
        char data[BUF_SIZE];
        recv(socket, data, BUF_SIZE, 0);
        std::cout << data;

        //if (recv(socket, data, BUF_SIZE, 0) != -1);
            //std::cout << data;
        //break;
    }
}

// send data to socket
bool Server::send_data(int socket, const char* data)
{
    if (send(socket, data, BUF_SIZE, 0) != -1)
        return true;
    return false;

}

// send data to all user
void Server::send_all(const char* data)
{
    for(auto user : users)
    {
        send_data(user, data);
    }
}

// LOGIC ERROR!! (must be inf loop)
void Server::start()
{
    std::cout << "start\n";
    while (true)
    {
        std::cout << "\nserver waiting for client...\n";
        sock = accept(listener, 0, 0);
        if (sock < 0)
        {
            perror("BAD CONNECTION WITH CLIENT");
            continue;
        }
        listen_user(sock); // ERROR!!!!
    }
    
}