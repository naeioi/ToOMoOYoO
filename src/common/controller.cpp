#include "net.h"
#include "controller.h"
#include "logger.h"
#include "utility.h"
#include <cstring>
#include <exception>
#include <memory>
using namespace std;

#ifdef DEBUG
#define BRKCHR '#'
#else
#define BRKCHR '\0'
#endif

namespace TMY {

Controller::Controller(int fd_, const SA* addr_, socklen_t addrlen_) {
    if(addrlen_ != sizeof(SA4))
        throw new std::exception();

	fd = fd_;
    memcpy(&addr, addr_, sizeof(SA));

    /* 默认1s超时 */
    timeout = { 1, 0 };
    blocking = false;
}

/* TODO */
int Controller::connect(const SA* addr, Controller_ptr& controller, bool blocking, timeval timeout) {
    int fd = socket(AF_INET, SOCK_STREAM, 0), n;

	setnb(fd);

    fd_set rset, wset;
	
	if( (n = ::connect(fd, addr, sizeof(SA))) < 0)
		if(terrno() != TEWOULDBLOCK)
			return -1;
	
	if(n == 0) /* done */
		return 0;
	
	FD_ZERO(&rset); FD_SET(fd, &rset);
	wset = rset;
	
	if( (n = select(fd+1, &rset, &wset, NULL, blocking ? NULL : &timeout)) == 0)
		return TTIMEOUT;
	
	if (n == 0)
		return TERROR;

	if(FD_ISSET(fd, &rset) || FD_ISSET(fd, &wset)) {
        char error[255];
		int len = sizeof(error);
		if(getsockopt(fd, SOL_SOCKET, SO_ERROR, error, (socklen_t *)&len) < 0)
			return TERROR;
	}
	else 
		return TERROR;
	
	controller = make_shared<Controller>(fd, addr, sizeof(SA));
	
	return 0;
}


int Controller::reconnect() {
	tclose(fd);

	shared_ptr<Controller> nc;

	int n;
	if ((n = connect(&addr, nc)) != 0)
		return n;

	*this = *nc;
	return 0;
}

int Controller::signup(const std::string& username, const std::string& password, SignupRes& signupRes) {
	return login(username, password, signupRes);
}

int Controller::login(const std::string& username, const std::string& password, LoginRes& loginRes) {
	
	/* Send Login */
	string msg = "Login\n";
	json header = {
		{"username", username},
		{"password", password}
	};
	msg += header.dump();
	int n = 0, m = 0;

	while (m < msg.size()) {
		blockt(fd, TREAD, &timeout);
		if ((m = send(fd, msg.c_str() + n, msg.length(), 0)) < 0)
			return -1;
		n += m;
	}

	blockt(fd, TREAD, &timeout);
	if ((m = send(fd, "\0", 1, 0)) < 0)
		return -1;

	logger("Sent login");

	/* Wait for response */
	unique_ptr<Readbuf_> readbuf(new Readbuf_(fd));
	msg = "";
	char buf[READBUFN];
	while ((m = readbuf->readto(buf, '\n')) > 0) {
		buf[m] = 0;
		msg += buf;
		if (buf[m - 1] == '\n') break;
	}

	if (m < 0)
		return m;

	if (m == 0)
		return TCLOSE;

	if (msg != "LoginRes\n") {
		logger("Receive %s but not Login", msg.c_str());
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

	*msg.rbegin() = 0;
	json loginres_ = json::parse(msg.c_str());
	loginRes = { loginres_["code"], loginres_["message"], loginres_["session"] };

	return 0;
}

int Controller::waitLogin(LoginReq& loginReq) {
	int type;
	return waitLoginSignup(loginReq, type);
}

int Controller::waitSignup(SignupReq& signupReq) {
	int type;
	return waitLoginSignup(signupReq, type);
}
// type == 0 => Login, type == 1 => signup
int Controller::waitLoginSignup(LoginReq& loginReq, int &type) {
	unique_ptr<Readbuf_> readbuf(new Readbuf_(fd));
	string msg;
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

	if (msg == "Login\n") {
		type = 0;
	}
	else if (msg == "Signup\n") {
		type = 1;
	}
	else {
		logger("Receive %s while expect Login", msg.c_str());
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
	auto loginReq_ = json::parse(msg.c_str());
	loginReq = {
		loginReq_["username"],
		loginReq_["password"]
	};

	return 0;
}

int Controller::sendLoginRes(const LoginRes&) {
	return 0;
}

int Controller::sendSignupRes(const SignupRes&) {
	return 0;
}

int Controller::makeSender(TunnelMode mode, Sender_ptr& sender) {
	return 0;
}

int Controller::makeReceiver(TunnelMode mode, Receiver_ptr& receiver) {
	return 0;
}

SA* Controller::Addr() {
	return &addr;
}


}