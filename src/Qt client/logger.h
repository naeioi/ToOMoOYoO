#include <QThread>
#include <QFile>
#include <QTime>
#include <QTextStream>
#include <iostream>
#include <QIODevice>
#include <QMutex>

#ifndef LOGGER_H
#define LOGGER_H

namespace TMY
{
const QString LOGFILEHEADDER = "./TMYClientLog";

class Logger : public QObject
{
    Q_OBJECT
public:
    static QString filename;
    static QTextStream ds;
    static QFile file;
    static void initilize();
    static void log(const QString);
};


}

#endif // LOGGER_H
