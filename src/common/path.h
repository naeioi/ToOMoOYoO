#ifndef __PATH_H
#define __PATH_H

#include "tmy.h"
#include <vector>
#include "json.hpp"

namespace TMY {
	typedef std::vector<string> PathArr;
	struct FilePath {
		std::string filename;
		PathArr pathArr;
		inline json& toJSON() {
			json r;
			std::string path = "";
			r["filename"] = filename;

			for(auto &dir: pathArr)
				path += "/" + dir;

			r["path"] = path;
			return r;
		}
	};
	typedef std::shared_ptr<FilePath> FilePath_ptr;
};

#endif