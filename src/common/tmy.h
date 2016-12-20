#ifndef __TMY_H
#define __TMY_H

/* 指定是客户机/服务器代码 */
// #define CLIENT
// #define SERVER

#include <memory>

typedef struct sockaddr_in SA4;
typedef struct sockaddr SA;

extern int tmyerrono; /* Global error code */
extern char *tmyerrstr; /* global error string */

namespace TMY {
	namespace net {
		class Controller;
		class Receiver;
		class Sender;
		class Listener;
	}
	struct Session;
	struct Auth;
	struct DirInfo;
};

#endif