#ifndef __CHUNK_H
#define __CHUNK_H

#include "tmy.h"

namespace TMY {

struct Chunk {
	int offset;
	int len;
};

class Chunks::public std::vector<Chunk> {
public:
	json toJSON();
}

typedef std::share_ptr<Chunks> Chunks_ptr;

}
#endif