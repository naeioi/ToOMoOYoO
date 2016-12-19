#ifndef __PULLREQ_H
#define __PULLREQ_H

#include "tmy.h"
#include <vector>
#include <string>
#include <ctime>
#include "path.h"

struct TMY::PullReqEntry {
	TMY::FilePath filePath;
	int offset;
	int len;
};

typedef std::share_ptr<PullReqEntry> TMY::PullReqEntry_ptr;
typedef std::vector<TMY::PullReqEntry_ptr> TMY::PullReq;
typedef std::share_ptr<TMY::PullReq> TMY::PullReq_ptr;

#endif