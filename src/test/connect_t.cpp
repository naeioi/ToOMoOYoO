#include "common/net.h"

int main(int argc, char** argv)
{
    if(argc < 3 ) {
        printf("Usage: %s <IP> <PORT>\n", argv[0]);
        exit(0);
    }

    Controller_ptr controller;

    SA4 addr;
    addr.sin_family = AF_INET;
    inet_aton(argv[1], &addr.sin_addr);
    addr.sin_port = htons(atoi(argv[2]));

    while(1) {
        int n = Controller::connect(addr, controller);
        if(n == 0) {
            printf("成功连接\n");
            return ;
        }
        else if(n == TTIMEOUT) {
            printf("超时等待\n");
        }
    }
    return 0;
}