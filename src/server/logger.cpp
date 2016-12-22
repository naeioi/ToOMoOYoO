#include "logger.h"
#include <stdarg.h>
#include <time.h>
#include <stdio.h>

static char timebuf[20];
static struct tm *sTm;
static time_t now;

static void updTime() {
	now = time(0);
	sTm = gmtime(&now);
	strftime(timebuf, sizeof(timebuf), TIMEFORMAT, sTm);
}

static void printMsg(
	const char *fname,
	int line,
	const char *func,
	MsgType msgType,
	Bool sysErr, 
	int err, 
	const char *format, 
	va_list ap) {
		#define BUFSIZE 500
		char buf[BUFSIZE], errText[BUFSIZE], userMsg[BUFSIZE];
		
		updTime();
		vsnprintf(userMsg, BUFSIZE, format, ap);
		
		if(sysErr)
			snprintf(errText, BUFSIZE, "[%s]", strerror(err));
		else 
			snprintf(errText, BUFSIZE, ":");
		
		snprintf(buf, BUFSIZE, "%s %s %s():%d | %s%s %s\n", 
			timebuf, fname, func, line,
			msgType == ERROR ? "ERROR" :
			msgType == LOG ? "LOG": 
			msgType == USAGEERR ? "UsageErr" :
			msgType == FATAL ? "FATAL" : "UNKNOWN",
			errText, userMsg);
		fputs(buf, stderr);
		fflush(stderr);
	}
	
void __errExit(const char *fname, int line, const char *func, const char *format, ...) {
	va_list ap;
	int savedErrno = errno;
	va_start(ap, format);
	printMsg(fname, line, func, ERROR, TRUE, errno, format, ap);
	va_end(ap);
	errno = savedErrno;
	exit(EXIT_FAILURE);
}

void __fatal(const char *fname, int line, const char *func, const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	printMsg(fname, line, func, FATAL, FALSE, 0, format, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

void __logger(const char *fname, int line, const char *func, const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	printMsg(fname, line, func, LOG, FALSE, 0, format, ap);
	va_end(ap);
}

void __usageErr(const char *fname, int line, const char *func, const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	printMsg(fname, line, func, USAGEERR, FALSE, 0, format, ap);
	va_end(ap);
}