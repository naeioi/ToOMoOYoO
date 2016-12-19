#include "logger.h"

QString TMY::Logger::filename;
QTextStream TMY::Logger::ds;
QFile TMY::Logger::file;

void TMY::Logger::initilize()
{
    filename = LOGFILEHEADDER;
    filename += QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
    filename += ".txt";
    file.setFileName(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    ds.setDevice(&file);
}

void TMY::Logger::log(const QString msg)
{
    file.open(QIODevice::Append | QIODevice::Text);

    ds << (QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm::ss : ")) << msg << "\n";

    file.close();
}
