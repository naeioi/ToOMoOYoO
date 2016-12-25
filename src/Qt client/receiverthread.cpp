#include "receiverthread.h"
#include <QFileInfo>
#define log(s) TMY::Logger::log(s)

using namespace TMY;

void ReceiverThread::run()
{
    mode = 0;
    while (1)
    {
        if (mode == 1)
            initSync();
        if (mode == 2)
            recvSync();
    }
}

void ReceiverThread::setMode(int mode_, QString path)
{
    mode = mode_;
    syncPath = path;
}

void ReceiverThread::setMainClient(MainClient *mc, TMY::Controller_ptr cp)
{
    mainclient = mc;
    controller = cp;
}

void ReceiverThread::initSync()
{
    while (controller->makeReceiver(0, receiver)!= 0)
        log("MakeReceiver timed out");

    DirInfo dirinfo;
    while (receiver->waitDirInfo(dirinfo) != 0)
        log("WaitDirInfo timed out");

    for (DirInfoEntry &entry : dirinfo)
    {
        QString ffpath = syncPath;
        ffpath += TMY::convert(entry.filePath);

        QFileInfo finfo;
        finfo.setFile(ffpath);

        if (finfo.exists())
        {
            QFile file(ffpath);
            file.open(QIODevice::ReadOnly);
            QCryptographicHash hash(QCryptographicHash::Algorithm::Md5);
            hash.addData(&file);
            std::string localmd5 = QString(hash.result().toHex).toStdString();

            if (localmd5 != entry.md5)
            {
                if (finfo.lastModified().toTime_t() > entry.modtime)
                    entry.filePath.filename += ".old";
                else
                {
                    QString newname = ffpath;
                    newname += ".old";
                    file.rename(newname);
                }
            }
            else
            {
                continue;
            }
        }

        QString fpath = syncPath;
        fpath += TMY::convert(entry.filePath);
        QString mpath = fpath;
        mpath += ".old";

        QFile file(fpath);
        file.open(QIODevice::WriteOnly);
        file.close();
        QFile mfile(mpath);
        mfile.open(QIODevice::WriteOnly);
        mfile.close();
    }

    emit writeReady();

    PullReq pulls;

    for (DirInfoEntry &entry : dirinfo)
    {
        LocalFileWriter writer(syncPath);
        writer.setFilePath(entry.filePath);

        PullReqEntry pullentry;
        while (writer.generatePullReqEntry(pullentry))
            pulls.push_back(pullentry);
        PullReq pullss;
    }

    receiver->sendPull(pulls);

    PushReq pushes;
    receiver->waitPush(pushes);

    for (PushReqEntry &entry : pushes)
    {
        LocalFileWriter writer(syncPath);
        writer.setFilePath(entry.filePath);
        writer.writePush(entry);
    }

    mode = 3;
    delete receiver;
    incrSync();
}

void ReceiverThread::incrSync()
{
    while (controller->makeReceiver(1, receiver) != 0)
        log("MakeReceiver timed out");



}
