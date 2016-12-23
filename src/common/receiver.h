#pragma once

#include "receiver.h"
#include "packets.h"
#include <functional>
// #include "progressinfo.h"

namespace TMY {

class Receiver {
private:
	int fd;
public:

	int waitDirInfo(DirInfo&);
	int sendPull(const PullReq&);
	int waitPush(PushReq_ptr&);
	~Receiver();
};

typedef std::shared_ptr<Receiver> Receiver_ptr;

}