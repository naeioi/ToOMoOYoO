#ifndef __SESSION_H
#define __SESSION_H

#include "tmy.h"
#include <ctime>

typedef struct TMY::Session {
	int uid;
	int sessionid;
	time_t estime; /* established time */
} Session;

typedef share_ptr<Session> TMY::Session_ptr;

#endif