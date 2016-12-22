#ifndef __PULLREQ_H
#define __PULLREQ_H

#include "tmy.h"
#include <vector>
#include <string>
#include <ctime>
#include "path.h"

namespace TMY {

/* 一条PullReq可能包含很多个PullReqEntry */
struct PullReqEntry {
	FilePath filePath;
	int offset;
	int len;
};

typedef std::shared_ptr<PullReqEntry> PullReqEntry_ptr;
typedef std::vector<PullReqEntry> PullReq;
typedef std::shared_ptr<PullReq> PullReq_ptr;


}
#endif