#include <cstdio>
#include "../../net.h"
using namespace TMY;

int main()
{
	int n;
	Controller_ptr controller;

	initsock();

	SA4 addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	n = inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	addr.sin_port = htons(2222);

	while ((n = Controller::connect((SA*)&addr, controller)) != 0) {
		if (n == TTIMEOUT) {
			printf("Timeout\n");
		}
	}

	printf("Connected !\n");
	LoginRes loginres;
	LoginReq loginReq = {"naeioi", "rocket", ""};
	SignupReq signupReq = { "naeioi", "rocket", "" };
	SignupRes signuperes;
	controller->login(loginReq, loginres);
	controller->signup(signupReq, signuperes);
	controller->makeReceiver(INIT, )
	return 0;
}