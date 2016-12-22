#ifndef __LISTENER_H
#define __LISTENER_H
#include "net.h"
#include "controller.h"
#include <functional>

namespace TMY {

//typedef std::function<int(Auth, Session&)> AuthService;

class Listener {
private:
    int fd;
public:
    Listener(): fd(-1) {}
    int listen(int port);
    //void setAuthService();
    Controller_ptr waitClient();
    void close();
};

}

#endif