#include "../include/client.hpp"

int main()
{
    Client client("Michael");
    client.cconnect(INADDR_LOOPBACK, 5001);
    for (size_t i = 0; i < 10; i++)
    {
        char data[20];
        std::cin >> data;
        client.send_data(data);
    }
    client.send_data("GOOD BYE!");
    return 0;
}