#include "tmy.h"
#include <ctime>

typedef struct Session{
	int uid;
	int sessionid;
	time_t 	estime; /* established time */
}Session;

typedef share_ptr<Session> Session_ptr;