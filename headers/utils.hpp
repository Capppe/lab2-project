#ifndef UTILS_HPP
#define UTILS_HPP

#include <QString>
#include <QTime>
#include <QDebug>

class Utils
{
public:
    Utils();

    static QString getTimeFormat(qint64 milliseconds);
};

#endif