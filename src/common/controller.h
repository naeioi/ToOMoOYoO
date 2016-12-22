#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "tmy.h"
#include "net.h"
#include "signupres.h"
#include "loginres.h"
#include "sender.h"
#include "receiver.h"
#include <functional>
#include <string>

namespace TMY {

enum TunnelMode { INIT, INCR, RECV };

class Controller;
typedef std::shared_ptr<Controller> Controller_ptr;

class Controller {
	friend class Listener;	
private:
	char addrstr[20];
	int fd;
	SA4 addr;
	Session session;
public:
	/* 以auth为凭证连接addr，同时设置对方要求建立receiver时的handler
	 * 失败返回 nullptr 
	 */
	//Controller() { fd = -1; } /* 禁止显式初始化，必须通过connect()工厂函数 */	
	Controller(int fd_, const SA4 addr_, socklen_t addrlen_);

	static Controller_ptr connect(SA addr);

	/* 重新连接 
	 * 失败返回 -1
	 */
	int reconnect();

	/* 注册 
	 * struct SignupRes {
	 *	 int code,
	 *	 string session,
	 *	 string message
	 * }
	 * 见protocol.md
	 */
	/* 小心：register是保留字 */
	SignupRes signup(std::string username, std::string password);

	/* 登陆 
	 * typedef SignupRes LoginRes;
	 */
	LoginRes login(std::string username, std::string password);

	 /* 建立 Sender 通道, 返回 Sender* 指针
	  * enum TunnelMode { INIT, INCR, RECV } 初次，增量，恢复
	  */	
	Sender_ptr makeSender(TunnelMode mode);

	/* 收到信道建立请求，自己的角色是 Receiver
	 * 使用回调函数处理
	 * 回调函数原型：
	 * void recvReqHandler(Receiver_ptr, TunnelMode);
	 */
	int setReceiverReqHandler(std::function<void(Receiver_ptr, TunnelMode)>);

	/* 返回地址 192.168.0.1:2777 */
	SA4 Addr();
};

}
#endif