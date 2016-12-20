#include "dirscanner.h"

void TMY::DirScanner::scan(QJsonArray &result,QString rootPath)
{
    QJsonObject node;

    QFileInfo finfo(rootPath);

    QDir dirobj(rootPath);
    TMY::Logger::log("scaning dir: ");
    TMY::Logger::log(rootPath);
    QStringList sublist = dirobj.entryList();
    for (int i = 2; i < sublist.size(); ++i)
        TMY::Logger::log(sublist[i]);
    TMY::Logger::log("scaning end ");
    TMY::Logger::log("");

    if (finfo.isDir())
    {
        QString path;
        for (int i = 2; i < sublist.size(); ++i)
        {
            path = rootPath;
            path += "/";
            path += sublist[i];
            scan(result, path);
        }
    }
    else
    {
        node["modtime"] = finfo.lastModified().toString();
        node["filename"] = finfo.fileName();

        QJsonArray pathList;

        pathList = QJsonArray::fromStringList(rootPath.split('/'));
        node["path"] = pathList;

        QFile file(rootPath);
        file.open(QIODevice::ReadOnly);
        QCryptographicHash hash(QCryptographicHash::Algorithm::Md5);
        hash.addData(&file);
        node["md5"] = QString(hash.result().toHex());
        result.append(node);
    }

}

void TMY::DirScanner::scanTo(QString rootPath, QString filepath)
{
    QFile file(filepath);
    file.open(QIODevice::WriteOnly);

    QJsonArray obj;
    scan(obj, rootPath);
    QJsonDocument doc(obj);
    file.write(doc.toJson());
}
