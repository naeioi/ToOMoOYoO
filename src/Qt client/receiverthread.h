#ifndef RECEIVERTHREAD_H
#define RECEIVERTHREAD_H

#include "common.h"
#include <QThread>
#include "mainclient.h"

namespace TMY
{
class ReceiverThread : public QThread
{
    Q_OBJECT
public:
    void run();
    void setMode(int mode_, QString path);
    void setMainClient(MainClient *, TMY::Controller_ptr);

signals:
    void writeReady();

private:
    int mode;
    Receiver *receiver;
    MainClient *mainclient;
    QString syncPath;
    TMY::Controller_ptr controller;
    void initSync();
    void recvSync();
};
}

#endif // RECEIVERTHREAD_H
