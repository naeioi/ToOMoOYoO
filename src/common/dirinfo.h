#ifndef __DIRINFO_H
#define __DIRINFO_H

#include "tmy.h"
#include <string>
#include <vector>
#include "chunks.h"
#include "path.h"
#include "json.hpp"

namespace TMY {

struct DirInfoEntry {
	FilePath filePath;
	time_t modtime;
	std::string md5;
	int len;
	/* 保证chunks按照offset升序排序 */
	Chunks chunks;
	json toJSON();
};

typedef std::shared_ptr<DirInfoEntry> DirInfoEntry_ptr;

class DirInfo: std::vector<DirInfoEntry_ptr> {
public:	
	json toJSON();
};

typedef std::shared_ptr<DirInfo> DirInfo_ptr;

}
#endif
