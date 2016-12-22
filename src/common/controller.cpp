#include "net.h"
#include <cstring>
#include <exception>
using namespace std;

namespace TMY {

Controller::Controller(int fd_, const SA4 addr_, socklen_t addrlen_) {
    if(addrlen_ != sizeof(SA4))
        throw new std::exception();

    memcpy(&addr, &addr_, sizeof(SA4));
}

/* TODO */
Controller_ptr Controller::connect(SA addr) {
    return nullptr;
}

int Controller::reconnect() {
    return 0;
}

SignupRes Controller::signup(const string& username, const string& password) {
    return {0, "", ""};
}

LoginRes Controller::login(const string& username, const string& password) {
    return {0, "", ""};
}

Sender_ptr Controller::makeSender(TunnelMode mode) {
    return nullptr;
}

int Controller::setReceiverReqHandler(function<void(Receiver_ptr, TunnelMode)> handler) {
    return 1;
}

SA4 Controller::Addr() {
    return addr;
}

}