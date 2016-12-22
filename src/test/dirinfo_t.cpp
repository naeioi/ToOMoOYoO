#include "common/packets.h"
#include <string>
#include "test.hpp"
using namespace std;
using namespace TMY;

/* 
 * Test for 
 *   chunks.cpp
 *   dirinfo.cpp
 *   path.cpp
 */

int main()
{
    /*-------------*/
    testbegin("FilePath1");
{ 
    FilePath f;
    f.filename = "v.mp4";
    for(int i = 0; i < 10; i++)
        f.pathArr.push_back(string("dir") + to_string(i));

    json j = f.toJSON();
    string filename_ = j["filename"];
    string path_ = j["path"];
    printf("filename=%s\npath=%s\n", filename_.c_str(), path_.c_str());
}
    testend();

    /*-------------*/
    testbegin("FilePath2");
{
    FilePath f = {"v.mp4", {"dir1", "dir2", "dir3"}};
    printf("%s\n", f.toJSON().dump(4).c_str());
}
    testend();

    /*-------------*/
    testbegin("Chunks");
{
    /* List initialization doesnt work */
    Chunks cs;
    cs.push_back({ 0, 1024 });
    cs.push_back({ 1024, 2048});

    printf("%s\n", cs.toJSON().dump(4).c_str());
}   
    testend();
    return 0;
}