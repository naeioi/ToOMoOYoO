#include "net.h"
#include "receiver.h"
#include "utility.h"
#include "logger.h"
#include "packets.h"
using namespace TMY;
using namespace std;

int Receiver::waitDirInfo(DirInfo& dirinfo) {
	unique_ptr<Readbuf_> readbuf(new Readbuf_(fd));
	string msg = "";
	char buf[READBUFN];

	int n, m;
	while ((m = readbuf->readto(buf, '\n')) > 0) {
		buf[m] = 0;
		msg += buf;
		if (buf[m - 1] == '\n') break;
	}

	if (m == 0)
		return TCLOSE;
	if (m < 0)
		return m;

	*msg.rbegin() = 0;

	if (msg != "DirInfo") {
		logger("Received %s but expect DirInfo", msg.c_str());
		return TERROR;
	}

	msg = "";
	while ((m = readbuf->readto(buf, BRKCHR)) > 0) {
		buf[m] = 0;
		msg += buf;
		if (buf[m - 1] == BRKCHR) break;
	}

	if (m == 0)
		return TCLOSE;
	if (m < 0)
		return m;
	*msg.rbegin() = 0;

	/* parse */

	pullreq.clear();
	json header = json::parse(msg.c_str());

	if (!header.is_array())
		throw new exception();

	for (auto &e : header) {
		PullReqEntry h;
		h.len = e["len"];
		h.offset = e["offset"];
		h.filePath.filename = e["filename"].dump();
		h.filePath.pathArr = move(str2PathArr(e["path"].dump()));
		pullreq.push_back(h);
	}

    return 0;
}

int Receiver::sendPull(const PullReq& pullreq) {
    return 0;
}

int Receiver::waitPush(PushReq_ptr& pushreq_ptr) {
    return 0;
}

Receiver::~Receiver() {
	tclose(fd);
}