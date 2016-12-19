#ifndef __SENDER_H
#define __SENDER_H

#include "tmy.h"
#include "pushreq.h"
#include "pullreq.h"

class TMY::Sender {
private:
	int fd;
public:
	int push(PushReq_ptr);
	TMY::PullReq_ptr waitPull();
	int sendDirInfo(TMY::DirInfo_ptr);
	~Sender();
};

#endif