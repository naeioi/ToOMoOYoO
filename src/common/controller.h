#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "tmy.h"
#include "Receiver.h"
#include "Sender.h"
#include <functional>
#include <string>

typedef share_ptr<Controller> Controller_ptr;
class Controller {
private:
	Controller(); /* 禁止显式初始化，必须通过connect()工厂函数 */	
	Session session;
public:
	/* 以auth为凭证连接addr，同时设置对方要求建立receiver时的handler
	 * 失败返回 nullptr 
	 */
	static Controller_ptr connect(SA addr);

	/* 重新连接 
	 * 失败返回 -1
	 */
	int reconnect();

	/* 注册 
	 * struct RegisterRes {
	 *	 int code,
	 *	 string session,
	 *	 string message
	 * }
	 * 见protocol.md
	 */
	RegisterRes register(std::string username, std::string password);

	/* 登陆 
	 * typedef ResgisterRes LoginRes;
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
	int setReceiverReqHandler(function<void(Receiver_ptr, TunnelMode)>);

	
};

#endif