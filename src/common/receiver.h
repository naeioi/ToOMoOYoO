#ifndef __RECEIVER_H
#define __RECEIVER_H

#include "tmy.h"
#include <functional>
#include "pushreq.h"
#include "pullreq.h"
// #include "progressinfo.h"

namespace TMY {

class Receiver {
private:
	int fd;
public:

	DirInfo waitDirInfo();
	int sendPull(const PullReq);
	PushReq_ptr waitPush();
	~Receiver();
};

}
#endif