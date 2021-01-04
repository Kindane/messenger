#include "../include/client.hpp"
#include <string>

// Send many data
void send_messages(Client client, int count)
{
    for (size_t i = 0; i < count; i++)
    {
        char data[BUF_SIZE];
        std::cin.getline(data, BUF_SIZE);
        client.send_data(data, sizeof(data), 0);
    }
}

int main()
{
    Client client("Michael");
    client.cconnect(INADDR_LOOPBACK, 3006);
    send_messages(client, 3);
    return 0;
}
