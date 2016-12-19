#include "dirinfo.h"
#include "path.h"
#include "json.hpp"
#include <string>
using namespace TMY;

int main()
{
    FilePath f;
    f.filename = "v.mp4";
    for(int i = 0; i < 10; i++)
        f.pathArr.push_back("dir" + i);
    json j = f.toJSON();
    string filename_ = j["filename"];
    string path_ = j["path"];
    printf("filename=%s\npath=%s\n", filename.c_str(), path.c_str());
    return 0;
}