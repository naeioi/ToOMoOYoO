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
	~Sender();

	/* 以下函数都是阻塞的 */

	int push(PushReq_ptr);	
	int sendDirInfo(DirInfo);
	PullReq waitPull();
};

typedef std::shared_ptr<Sender> Sender_ptr;

}

#endif