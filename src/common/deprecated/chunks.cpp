#include "chunks.h"
#include "json.hpp"
using namespace TMY;

json Chunks::toJSON() {
    json r;
		for(auto &c:*this) {
			r.push_back({
				{"offset", c.offset},
				{"len", c.len}
			});
		}
		return r;
}
