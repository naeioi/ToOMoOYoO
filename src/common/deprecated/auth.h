#ifndef __AUTH_H
#define __AUTH_H

#include "tmy.h"
#include <string>

namespace TMY {

struct Auth {
	std::string username;
	std::string passwd;
};

typedef std::share_ptr<Auth> Auth_ptr;

}

#endif