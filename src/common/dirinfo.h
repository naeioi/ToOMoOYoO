#ifndef __DIRINFO_H
#define __DIRINFO_H

#include "tmy.h"
#include <string>
#include <vector>
#include "chunks.h"

struct TMY::DirInfoEntry {
	std::string path;
	time_t modtime;
	string md5,
	int len,
	/* ±£÷§chunks∞¥’’offset…˝–Ú≈≈–Ú */
	std::vector<Chunks> chunks;
};

typedef share_ptr<DirInfoEntry> TMY::DirInfoEntry_ptr;
typedef vector<DirInfoEntry_ptr> TMY::DirInfo;
typedef share_ptr<DirInfo> TMY::DirInfo_ptr;

#endif
