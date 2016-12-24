#pragma once
#include <vector>
#include "net.h"
#include <string>

template <int const N>
class Readbuf {
private:
    int fd;
	char lastdet;
    char buf[N + 1];	
    char *t;
public:
    Readbuf(int fd_);
    int readto(char *b, char det = '\0');
    //int readn(char *b, int len);

    bool blocking;
    timeval timeout;
};

template <int N>
Readbuf<N>::Readbuf(int fd_) {
	lastdet = -1;
	blocking = 0;
	timeout = { 1, 0 };
	t = buf;
	fd = fd_;
}

template <int N>
int Readbuf<N>::readto(char *b, char det) {

	if (det != lastdet && t-buf > 0) {
		int n = t - buf;
		char *p = buf;
		bool ok = false;
		while (n > 0) {
			if (*p == det) {
				++p; --n;
				ok = true;
				break;
			}
			++p; --n;
		}
		if (ok) {
			int len = p - buf;
			memcpy(b, buf, len);
			memcpy(buf, p, n);
			t = buf + n;
			return len;
		}
	}
	lastdet = det;

	while (t-buf < N / 2) {

#ifdef DEBUG
		timeval tv = { 30, 0 };
		int flags = blockt(fd, TREAD, &tv);
#else
		int flags = blockt(fd, TREAD);
#endif


		if (!(flags | TREAD)) {
			return -1;
		}
		int n = recv(fd, t, N - (t - buf), 0);
		if (n <= 0) {
			return n;
		}
		bool ok = false;
		while (n > 0) {
			if (*t == det) {
				++t; --n;
				ok = true;
				break;
			}
			++t; --n;
		}
		if (ok) {
			int len = t - buf;
			memcpy(b, buf, len);
			memcpy(buf, t, n);
			t = buf + n;
			return len;
		}
	}

	int len = t - buf;
	memcpy(b, buf, len);
	t = buf;

	return len;
}

#define READBUFN 2048
typedef Readbuf<READBUFN> Readbuf_;

inline std::string time2str(const time_t &t) {
	char buf[30];
	tm tm_;
	localtime_s(&tm_, &t);
	strftime(buf, 20, "%Y-%m-%dT%H:%M:%SZ", &tm_);
	return std::string(buf);
}