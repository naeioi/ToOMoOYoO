#ifndef __PATH_H
#define __PATH_H

#include "tmy.h"
#include <vector>
#include "json.hpp"

namespace TMY {
	typedef std::vector<std::string> PathArr;
	struct FilePath {
		std::string filename;
		PathArr pathArr;
		json toJSON();
	};
	typedef std::shared_ptr<FilePath> FilePath_ptr;
};

#endif