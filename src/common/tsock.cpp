#include "tsock.h"
#include "errno.h"
#include <assert.h>

#ifdef _WIN32
void setnb(int fd) {
    unsigned long on = 1;
    ioctlsocket(fd, FIONBIO, &on);
}

void tclose(int fd){
	closesocket(fd);
} 

int terrno() {
    return WSAGetLastError();
}

void initsock() {
	WSADATA wsaData;
	int iResult;
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	assert(iResult == 0);
}

#elif __linux__ 

void tclose(int fd) {
    close(fd);
}

void setnb(int fd) {
    int oflag = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, oflag | O_NONBLOCK);
}


#endif

