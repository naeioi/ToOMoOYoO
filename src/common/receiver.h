#ifndef __RECEIVER_H
#define __RECEIVER_H

#include "tmy.h"
#include <functional>
#include "pushreq.h"
#include "pullreq.h"
#include "progressinfo.h"

class TMY::Receiver {
private:
	int fd;
public:
	TMY::TDirInfo_ptr waitDirInfo();
	int sendPull(const TMY::PullReq_ptr);
	TMY::TPushReq_ptr waitPush(std::function<void(ProgressInfo)> progressHandler);
	~Receiver();
};

#endif