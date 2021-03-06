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

bool Server::setup(int connections)
{
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("CANNOT BIND SOCKET");
        exit(BIND_ERROR);
    }
    else
    {
        listen(listener, connections);
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
    users.push_back(&socket);
    while (true)
    {
        char data[BUF_SIZE];
        //std::cout << "\naccept data...\n";

        if (recv(socket, data, BUF_SIZE, 0) <= 0)
        {
            std::cout << "\nSomeone of the users disconnected\n";

            // ебать костыль придумал 0_0
            for (int i = 0; i < users.size(); i++)
            {
                if (users[i] == &socket)
                {
                    users.erase(users.begin()+i); 
                    break;
                }
            }
            
            break;
        }
        std::cout << data;
        send_all(data);
        continue;
    }
}

/*
* <s>: socket
* <buf>: message
* <len>: length of message,
* <flags>: flags to send (default=0)
* returns: if bad: -1 else: count of sended bytes
*/
int Server::send_data(int s, const char *buf, int len, int flags)
{
    int total = 0; // sended
    int n;         // count of bytes

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

void Server::send_all(const char *data)
{
    for (auto user : users)
    {
        // <user> is user socket
        std::cout << "\n[DEBUG] send " << data << " to " << *user << std::endl;
        if (send_data(*user, data, sizeof(data), 0) != -1)
            continue;
        else
            std::cout << "can't send " << data << " to " << *user;
    }
}

void Server::start()
{
    std::cout << "Server waiting for users...\n";
    while (true)
    {
        // std::cout << "\nserver waiting for client...\n";
        sock = accept(listener, 0, 0); // accept connection
        if (sock < 0)
        {
            perror("BAD CONNECTION WITH CLIENT");
            continue;
        }
        std::cout << "\nNew user connected...\n";
        std::thread listen_thread([&]() { listen_user(sock); });
        listen_thread.detach();
    }
}
