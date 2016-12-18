```cpp
TMY
	net
		Controller
			typedef share_ptr<Controller> Controller_ptr;
			Controller(sockaddr_in remote_addr, Auth auth, function<void(Receiver_ptr)> receiveRequestHandler);
			
		Sender
			typedef share_ptr<Sender> Sender_ptr;
			Sender(Controller_ptr);
			
			void sendDir(DirInfo); /* 用抛出处理异常，见std::Exception */
			PullReq waitPull();
			void push(PushReq);
		Receiver
			typedef share_ptr<Receiver> Receiver_ptr;
			Receiver(Controller_ptr);
			
			DirInfo waitDirInfo();
			void pull(PullReq);
			PushReq waitPush();
```			