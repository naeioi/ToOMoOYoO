#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <iostream>
#include <logger.h>
#include <QFile>
#include <QCryptographicHash>

#ifndef DIRSCANNER_H
#define DIRSCANNER_H

namespace TMY
{

class DirScanner : public QObject
{
    Q_OBJECT
public:
    void scan(QJsonArray &result, QString rootPath);
    void scanTo(QString rootPath, QString filepath);
private:

};
}

#endif // DIRSCANNER_H
