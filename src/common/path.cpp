#include "path.h"
#include "json.hpp"
using namespace TMY;

json FilePath::toJSON() {
    std::string path = "";

    for(auto &dir: pathArr)
        path += "/" + dir;

    return json({
        {"filename", filename},
        { "path", path }
    });
}