#include "dirinfo.h"
#include "json.hpp" 
namespace TMY {

json DirInfoEntry::toJSON() {
    json r;
    
    json _filePath = std::move(filePath.toJSON());
    r['filename'] = std::move(_filePath['filename']);
    r['path'] = std::move(_filePa['path']);

    char timebuf[25];
    /* "2011-10-08T07:07:09Z" */
    /* http://stackoverflow.com/questions/9527960/how-do-i-construct-an-iso-8601-datetime-in-c */
    strftime(timebuf, sizeof(timebuf), "%FT%TZ");
    r['modtime'] = timebuf;

    r['md5'] = md5;
    r['len'] = len;

    /* Dont send chunks */
}

json& DirInfo::toJSON() {
    json r;
    for(int i = 0; i < size(); i++){
        r.push_back(std::move(get(i).toJSON()));
    }
    return r;
}

}