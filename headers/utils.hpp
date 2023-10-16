#ifndef UTILS_HPP
#define UTILS_HPP

#include <QString>
#include <QTime>
#include <QList>
#include <QPair>
#include <QDebug>

class Utils
{
public:
    Utils();

    static QString getTimeFormat(qint64 milliseconds);
    static QList<QPair<QString, QString>> parseFileContent(QList<QString> content);
};

#endif
