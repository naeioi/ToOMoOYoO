/* 封装所有自定义数据类型 */
#pragma once
#include "tmy.h"
#include "json.hpp"
#include <exception>
namespace TMY {

/* ---------- *
 *    Auth
 *------------*/
struct Auth {
	std::string username;
	std::string passwd;
};
typedef std::shared_ptr<Auth> Auth_ptr;

/* ----------- *
 *    Buffer
 *-------------*/
class Buffer {
private:
    char *data;
public:
    Buffer() {
        data = NULL;
    }
    Buffer(char * data_) {
        data = data_;
    }   
    ~Buffer() {
        try {
            delete data;
        }
        catch(std::exception e) {}
    }
    char* raw() {
        return data;
    }
};

/* ----------- *
 *    Chunks
 *-------------*/
struct Chunk {
	int offset;
	int len;
};

class Chunks:public std::vector<Chunk> {
public:
	json toJSON();
};

typedef std::shared_ptr<Chunks> Chunks_ptr;

/* -------------- *
 *  FilePath, PathArr
 *----------------*/
typedef std::vector<std::string> PathArr;
struct FilePath {
    std::string filename;
    PathArr pathArr;
    json toJSON();
};
typedef std::shared_ptr<FilePath> FilePath_ptr;
}

/* ------------ *
 *    DirInfo
 *--------------*/
struct DirInfoEntry {
	TMY::FilePath filePath;
	time_t modtime;
	std::string md5;
	int len;
	/* 保证chunks按照offset升序排序 */
	TMY::Chunks chunks;
	json toJSON();
};

typedef std::shared_ptr<DirInfoEntry> DirInfoEntry_ptr;

class DirInfo: std::vector<DirInfoEntry_ptr> {
public:	
	json toJSON();
};

typedef std::shared_ptr<DirInfo> DirInfo_ptr;

/* -------------- *
 *    SignupReq
 *    LoginReq
 *----------------*/
struct SignupReq {
    std::string username;
    std::string password;
};
typedef SignupReq LoginReq;

/* -------------- *
 *    SignupRes
 *    LoginRes
 *----------------*/
struct SignupRes {
        int code;
        std::string message;
        std::string session;
    };

typedef SignupRes LoginRes;

/* -------------- *
 *  PullReq
 *----------------*/

/* 一条PullReq可能包含很多个PullReqEntry */
struct PullReqEntry {
	TMY::FilePath filePath;
	int offset;
	int len;
};

typedef std::shared_ptr<PullReqEntry> PullReqEntry_ptr;
typedef std::vector<PullReqEntry> PullReq;
typedef std::shared_ptr<PullReq> PullReq_ptr;

/* -------------- *
 *  PushReq
 *----------------*/

struct PushReqEntry {
	TMY::FilePath filePath;
	int offset;
	int len;
	const char* buffer;
};

typedef std::shared_ptr<PushReqEntry> PushReqEntry_ptr;
typedef std::vector<PushReqEntry> PushReq;
typedef std::shared_ptr<PushReq> PushReq_ptr;

/* -------------- *
 *  Session
 *----------------*/

struct Session {
	int uid;
	int sessionid;
	time_t estime; /* established time */
};

typedef std::shared_ptr<Session> Session_ptr;