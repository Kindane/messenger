#include "../include/server.hpp"

int main()
{
    Server server(INADDR_ANY, 3009);
    server.setup(4);
    server.start();

    return 0;
}