# Auth 登陆&验证
服务器由Listener，客户端由Controller::connect建立一个控制信道。控制信道由Controller管理。
Controller解析到来的所有数据包，并调用提供给他的回调函数

- Register 注册
- Login 登陆
- DirInfo 发送
- MD5REQ
- MD5RES

对每个函数Controller既提供

Controller本身不提供验证服务，也不记录会话号(session number)
