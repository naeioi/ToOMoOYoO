#include "common/tmy.h"
#include "common/net.h"
#include "server/logger.h"
using namespace TMY;

void clientHandler(Controller_ptr cli) {
    logger("In child: client");
    
}

#define DEFAULT_PORT 2222

int main(int argc, char** argv)
{
    int port;
    if(argc == 1) port = DEFAULT_PORT;
    else port = atoi(argv[1]);
    
    Listener listener;

    if(listener.listen(port) < 0) {
        errExit("Fail to bind port %d", port);
    }

    logger("Listening on port %d", port);

    Controller_ptr controller;
    while((controller = listener.waitClient()) != nullptr) {
        switch(fork()) {
            case 0: /* child */
                listener.close(); /* unneeded copy */
                clientHandler(controller);
                break;
            case -1: /* fail */
                errExit("Fail to fork");
            default:
                SA4 cliaddr = controller->Addr();
                logger("New client from %s", inet_ntoa(cliaddr.sin_addr));
                break;
        }
    }
}