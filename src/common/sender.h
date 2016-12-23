#pragma once

#include "sender.h"
#include "packets.h"

namespace TMY {

class Sender {
private:
	int fd;
public:
	~Sender();

	int push(const PushReq&);	
	int sendDirInfo(const DirInfo&);
	int waitPull(PullReq&);
};

typedef std::shared_ptr<Sender> Sender_ptr;

}
