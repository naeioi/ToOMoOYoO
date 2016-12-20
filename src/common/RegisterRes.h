#ifndef __REGISTERRES_H
#define __REGISTERRES_H
#include <string>

namespace TMY {
    struct ResgisterRes{
        int code;
        std::string message;
        std::string session;
    };
}

#endif 