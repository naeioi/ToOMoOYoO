#ifndef __PUSHREQ_H
#define __PUSHREQ_H

#include "tmy.h"
#include <string>
#include <vector>
#include "path.h"

namespace TMY {

struct PushReqEntry {
	FilePath filePath;
	int offset;
	int len;
	const char* buffer;
};

typedef std::shared_ptr<PushReqEntry> PushReqEntry_ptr;
typedef std::vector<PushReqEntry> PushReq;
typedef std::shared_ptr<PushReq> PushReq_ptr;

}
#endif