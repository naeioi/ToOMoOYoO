#ifndef __SENDER_H
#define __SENDER_H

#include "tmy.h"
#include "pushreq.h"
#include "pullreq.h"

namespace TMY {

class Sender {
private:
	int fd;
public:
	int push(PushReq_ptr);
	PullReq_ptr waitPull();
	int sendDirInfo(DirInfo_ptr);
	~Sender();
};

}

#endif