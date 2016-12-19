#ifndef __CHUNK_H
#define __CHUNK_H

#include "tmy.h"

struct TMY::Chunks {
	int offset;
	int len;
};
typedef share_ptr<Chunks> Chunks_ptr;

#endif