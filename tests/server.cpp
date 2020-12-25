#include "../include/server.hpp"

int main()
{
    Server server(INADDR_ANY, 5001);
    server.setup();
    server.start();
    
    return 0;
}