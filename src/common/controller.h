#include "tmy.h"
#include "Receiver.h"
#include "Sender.h"

typedef share_ptr<Controller> Controller_ptr;
class Controller {
private:
	Controller(); /* 禁止显式初始化，必须通过connect()工厂函数 */
	Session session;
public:
	/* 以auth为凭证连接addr，同时设置对方要求建立receiver时的handler */
	Controller_ptr connect(SA addr, Auth auth, function<void(Receiver_ptr)> receiverReqHandler = nullptr);
	/* 接受生成的Receiver*指针 */
	int setReceiverReqHandler(function<void(Receiver_ptr)>);
	Sender_ptr makeSender(DirInfo_ptr dirInfo = nullptr);
	int reconnect();
}