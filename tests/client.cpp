#include "../include/client.hpp"
#include <string>

int main()
{
    Client client("Michael");
    client.cconnect(INADDR_LOOPBACK, 3004);
    /*
    for (size_t i = 0; i < 10; i++)
    {
        std::string data;
        std::cin >> data;
        client.send_data(data.c_str());
    }
    */
    client.send_data("hello, server!!!!");
    return 0;
}