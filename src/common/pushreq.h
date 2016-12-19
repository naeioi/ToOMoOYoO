#ifndef __PUSHREQ_H
#define __PUSHREQ_H

#include "tmy.h"
#include <string>
#include <vector>
#include "path.h"

struct TMY::PushReqEntry {
	TMY::FilePath filePath;
	int offset;
	int len;
	char* buffer;
};

typedef share_ptr<TMY::PushReqEntry> TMY::PushReqEntry_ptr;
typedef std::vector<PushReqEntry_ptr> TMY::PushReq;
typedef share_ptr<PushReq> TMY::PushReq_ptr;

#endif