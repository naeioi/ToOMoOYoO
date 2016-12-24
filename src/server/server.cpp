#include "common/tmy.h"
#include "common/net.h"
#include "logger.h"
#include "mysql/mysql.h"
#include "common/json.hpp"
#include <string>
#include <memory>
using namespace std;
using namespace TMY;

typedef share_ptr<Readbuf_> Rdbuf_ptr;

struct DHeader {
    string type;
    json header;
    int read(Rdbuf_ptr readbuf);
};

int DHeader::read(Rdbuf_ptr readbuf) {
    string msg;
    char buf[READBUFN];
    int n, m;

    while((n = readbuf->readto("\n")) > 0) {
        buf[n] = 0;
        msg += buf;
        if(buf[n-1] == '\n') break;
    }

    if(m < 0)
        return m;
    if(m == 0)
        return TCLOSE;
    
    // last byte is '\n'
    *msg.rbegin() = 0;
    type = msg;

    /* header */

    while((n = readbuf->readto("\0")) > 0) {
        buf[n] = 0;
        msg += buf;
        if(buf[n-1] == '\0') break;
    }

    if(m < 0)
        return m;
    if(m == 0)
        return TCLOSE;

    header = json.parse(msg.c_str());
    
    return 0;
}

void client(int fd) {
    logger("In child!");
    DHeader dh;
    
    shared_ptr<Readbuf_> readbuf(new Readbuf_(fd));
    dh.read(readbuf);
    printf("Type: %s\n", dh.type);
    close(fd);
}

int main(int argc, char argv**)
{

    int port;
    if(argc == 1) port = DEFAULT_PORT;
    else port = atoi(argv[1]);
    
    SA4 addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    int fd;
    if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    if(bind(fd, (const SA*) &addr, sizeof(addr)) < 0) {
        return -1;
    }

    #define BACKLOG 100
    listen(fd, BACKLOG);

    SA4 cliaddr;
    socklen_t len;
    while(1) {
        int clifd = accept(fd, (SA*)&cliaddr, &len);
        switch(fork()) {
            case 0:
                close(fd);
                client(clifd);
                break;
            case -1;
            default:
                logger("New client from %s:%d\n", inet_ntoa(their_addr.sin_addr), port);
                break;
        }
    }
}