#ifndef DBUSWORKER_HPP
#define DBUSWORKER_HPP

#include <QDBusInterface>
#include <QDBusReply>
#include <QObject>
#include <QThread>
#include <QDebug>

#include "bluetooth.hpp"

class DBusWorker : public QObject
{
    Q_OBJECT

public:
    DBusWorker(QObject *parent = nullptr);

public slots:
    void operate();

signals: 
    void result(uint32_t pos);
    void error(const QString &message);
};

#endif