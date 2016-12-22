#include "common/tmy.h"
#include "common/net.h"
#include "logger.h"
using namespace TMY;

void clientHandler(Controller_ptr cli) {
    logger("In child: client");
    return 0;
}

int main(int argc, char argv**)
{
    int port;
    if(argc == 1) port = DEFAULT_PORT;
    else port = atoi(argv[1]);
    
    Listener listener;

    if(listener.listen(port) < 0) {
        errExit("Fail to bind port %d", port);
    }

    Controller_ptr controller;
    while((controller = listernr.waitClient()) != nullptr) {
        switch(fork()) {
            case 0: /* child */
                listener.close(); /* unneeded copy */
                handlerNewClient(controller);
                break;
            case -1: /* fail */
                errExit("Fail to fork");
            default:
                logger("New client from %s", controller.addrStr());
                break;
        }
    }
}