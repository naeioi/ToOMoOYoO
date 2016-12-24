﻿#include "tmy.h"
#include "packets.h"
#include "json.hpp"
using namespace TMY;

/* ---------- *
 *    Chunks
 *------------*/
json Chunks::toJSON() const {
    json r;
		for(auto &c:*this) {
			r.push_back({
				{"offset", c.offset},
				{"len", c.len}
			});
		}
		return r;
}

/* ---------- *
 *  DirInfo
 *------------*/

json DirInfoEntry::toJSON() const {
    json _filePath = std::move(filePath.toJSON());

    /* "2011-10-08T07:07:09Z" */
    /* http://stackoverflow.com/questions/9527960/how-do-i-construct-an-iso-8601-datetime-in-c */
    char timebuf[25];

	struct tm _tm;
#ifdef _WIN32
	localtime_s(&_tm, &modtime);
    strftime(timebuf, sizeof(timebuf), "%FT%TZ", &_tm);
#elif __linux__
	strftime(timebuf, sizeof(timebuf), "%FT%TZ", localtime(&modtime));
#endif

    return json({
        {"modtime", timebuf},
        {"filename", std::move(_filePath["filename"])},
        {"path", std::move(_filePath["path"])},
        {"md5", md5},
        {"len", len}
    });
    /* Dont send chunks */
}

json DirInfo::toJSON() const {
    json r;
    for(int i = 0; i < size(); i++){
        r.push_back(std::move(at(i).toJSON()));
    }
    return r;
}

/* ---------- *
 *  FilePath
 *------------*/

json FilePath::toJSON() const {
    std::string path = "";

    for(auto &dir: pathArr)
        path += "/" + dir;

    return json({
        {"filename", filename},
        { "path", path }
    });
}


PathArr TMY::str2PathArr(const std::string & s)
{
	PathArr r;
	std::string dir = "";
	for (int i = 1; i < s.size(); i++) {
		if (s[i] == '/') {
			r.push_back(dir);
			dir = "";
		}
		else dir += s[i];
	}

	if (!dir.empty())
		r.push_back(dir);
	return r;
}
