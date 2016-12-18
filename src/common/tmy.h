#include <memory>

typedef struct sockaddr_in SA4;
typedef struct sockaddr SA;

extern int tmyerrono; /* Global error code */
char *tmyerrstr; /* global error string */

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

