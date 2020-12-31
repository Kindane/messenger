#include "include/server.hpp"

Server::Server(in_addr_t __addr, in_port_t __port)
{
    // initialize server address
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

Server::~Server()
{
    // send_all("\n\nBAD CONNECTION WITH SERVER...\n\n");
    close(sock);
    close(listener);
}

bool Server::setup()
{
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("CANNOT BIND SOCKET");
        exit(BIND_ERROR);
    }
    else
    {
        listen(listener, 3); // ready for accept users
        return true;
    }
}

void Server::listen_user(int socket)
{
    if (socket < 0)
    {
        std::cout << "Bad connection\n";
        return;
    }
    // users.push_back(socket);
    while (true)
    {
        char data[BUF_SIZE];
        std::cout << "\naccept data...\n";

        // error! inf repeating
        if (recv(socket, data, BUF_SIZE, 0) <= 0)
        {
            perror("RECV");
            std::cout << "\nNo data, sorry, bye.\n";
            break;
        }
        std::cout << data;
        continue;
    }
}

int Server::send_data(int s, char *buf, int len, int flags)
{
    int total = 0; // sended
    int n; // count of bytes

    while (total < len)
    {
        n = send(s, buf + total, len - total, flags);
        if (n == -1)
            break;
        total += n;
    }

    // if all is good, return <total>, else -1
    return (n == -1 ? -1 : total);
}

void Server::send_all(char *data)
{
    for (auto user : users)
    {
        // <user> is user socket
        send_data(user, data, sizeof(data), 0);
    }
}

void Server::start()
{
    std::cout << "start\n";
    while (true)
    {
        std::cout << "\nserver waiting for client...\n";
        sock = accept(listener, 0, 0); // accept connection
        if (sock < 0)
        {
            perror("BAD CONNECTION WITH CLIENT");
            continue;
        }
        // there is must be multi-threading or async
        listen_user(sock); // ERROR!!!!
    }
}
