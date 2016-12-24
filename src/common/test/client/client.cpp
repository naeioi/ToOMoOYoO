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
	Receiver_ptr receiver;
	Sender_ptr sender;
	PullReq pullreq = { { {"v.mp4", {"video", "files"}}, 0, 10 } };
	DirInfo dirinfo;
	PushReq pushreq;

	controller->login(loginReq, loginres);
	controller->signup(signupReq, signuperes);
	/* receiver test */
	controller->makeReceiver(INIT, receiver);
	receiver->sendPull(pullreq);
	receiver->waitDirInfo(dirinfo);
	receiver->waitPush(pushreq);
		
	/* sender test */
	pushreq = { { { "v.mp4",{ "video", "files" } }, 0, 10, "hello, world" } };
	controller->makeSender(INIT, sender);
	sender->push(pushreq);
	sender->sendDirInfo(dirinfo);
	sender->waitPull(pullreq);
	return 0;
}