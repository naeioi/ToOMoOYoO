# 源代码结构
```
.
├── build 生成测试用程序
├── common C/S共有代码
│   ├── auth.h
│   ├── buffer.h
│   ├── chunks.cpp
│   ├── chunks.h
│   ├── CMakeLists.txt
│   ├── controller.cpp
│   ├── controller.h
│   ├── dirinfo.cpp
│   ├── dirinfo.h
│   ├── json.hpp
│   ├── listener.cpp
│   ├── listener.h
│   ├── loginres.h
│   ├── net.h # 网络模块总公用头
│   ├── path.cpp
│   ├── path.h
│   ├── pullreq.h
│   ├── pushreq.h
│   ├── receiver.h
│   ├── sender.h
│   ├── session.h
│   ├── signupres.h
│   ├── tmy.h
│   └── tsock.h # socket跨平台头文件。只需要include tsock.h
├── main.cpp
├── server
│   ├── CMakeLists.txt
│   ├── logger.cpp
│   ├── logger.h
│   └── server.cpp
├── test # 测试用程序
│   ├── CMakeLists.txt
│   ├── controller_t.cpp
│   ├── dirinfo_t.cpp
│   ├── hello.cpp
│   └── test.hpp
└── tree.txt
```