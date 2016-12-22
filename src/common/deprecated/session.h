#ifndef __SESSION_H
#define __SESSION_H

#include "tmy.h"
#include <ctime>

namespace TMY {

typedef struct Session {
	int uid;
	int sessionid;
	time_t estime; /* established time */
} Session;

typedef std::shared_ptr<Session> Session_ptr;

}
#endif