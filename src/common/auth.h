#ifndef __AUTH_H
#define __AUTH_H

#include "tmy.h"
#include <cstring>

struct TMY::DirInfo {
	string username;
	string passwd;
};

typedef share_ptr<Auth> TMY::Auth_ptr;

#endif