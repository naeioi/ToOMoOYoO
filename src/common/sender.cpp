#include "packets.h"
#include "sender.h"
using namespace TMY;

int Sender::push(const PushReq& pushReq) {
    return 0;
}

int Sender::sendDirInfo(const DirInfo& dirinfo) {
    return 0;
}

int Sender::waitPull(PullReq&) {
    return 0;
}

Sender::~Sender() {
    
}
