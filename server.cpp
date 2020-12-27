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

// bind && getting ready for accept users...
bool Server::setup()
{
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
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
        if (socket < 0)
        {
            std::cout << "Bad connection\n";
            break;
        }
        char data[BUF_SIZE];
        std::cout << "\naccept data...\n";

        // error! inf repeating
        if (recv(socket, data, BUF_SIZE, 0) > 0)
            ;
        {
            std::cout << data;
            continue;
        }
        std::cout << "\nNo data, sorry, bye.\n";
        break;
    }
}

// send data to socket
bool Server::send_data(int socket, const char *data)
{
    if (send(socket, data, BUF_SIZE, 0) != -1)
        return true;
    return false;
}

// send data to all user
void Server::send_all(const char *data)
{
    for (auto user : users)
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
        sock = accept(listener, 0, 0); // correct
        //sock = accept(listener, (struct sockaddr*)&addr, 0); // dn
        if (sock < 0)
        {
            perror("BAD CONNECTION WITH CLIENT");
            continue;
        }
        listen_user(sock); // ERROR!!!!
    }
}