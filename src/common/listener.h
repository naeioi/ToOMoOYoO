#ifndef __LISTENER_H
#define __LISTENER_H
#include "tmy.h"
#include "session.h"
#include <functional>

namespace TMY {

//typedef std::function<int(Auth, Session&)> AuthService;

class Listener {
private:
public:
    int listen(int port);
    //void setAuthService();
    Controller_ptr waitClient();
    void close();
};

}

#endif