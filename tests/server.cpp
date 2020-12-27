#include "../include/server.hpp"
// TODO fix bug
/*bug: 
server forever repeat a last sended message.
for example:
client sent "hello, server!!!!"
and server repeat
"accept data...
hello, server!!!!
accept data...
hello, server!!!
"... forever.
NEED TO BE FIXED!!!
*/

int main()
{
    Server server(INADDR_ANY, 5004);
    server.setup();
    server.start();

    return 0;
}