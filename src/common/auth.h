#include "tmy.h"
#include <cstring>

struct TMY::DirInfo {
	string username;
	string passwd;
};

typedef share_ptr<Auth> Auth_ptr;