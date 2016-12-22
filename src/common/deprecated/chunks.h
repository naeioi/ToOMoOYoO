#ifndef __CHUNK_H
#define __CHUNK_H

#include "tmy.h"
#include <vector>
#include "json.hpp"

namespace TMY {

struct Chunk {
	int offset;
	int len;
};

class Chunks:public std::vector<Chunk> {
public:
	json toJSON();
};

typedef std::shared_ptr<Chunks> Chunks_ptr;

}
#endif