#pragma once

#include "common.h"
#include <fstream>

namespace TMY
{

    class LocalFileWriter
    {
    public:
        LocalFileWriter(QString syncPath_);
        void setFilePath(const FilePath);
        bool generatePullReqEntry(PullReqEntry);
        void writePush(const PushReqEntry &pushReq);
        bool finished;
    private:
        QFile file;
        FilePath filePath;
        QString path, metaPath;
        QString syncPath;
        Chunks chunks;
        const std::string METATAIL = ".tmydownload";
        void updateChunks();

    };

    class LocalFileReader
    {
    public:
        LocalFileReader(QString syncPath_);
        void setFilePath(const FilePath);
        PushReq generatePushReqEntry(PullReq);
    private:
        QFile file;
        FilePath filePath;
        QString path;
        QString syncPath;
    };

}
