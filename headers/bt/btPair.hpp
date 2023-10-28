#ifndef BTPAIR_HPP
#define BTPAIR_HPP

#include <QDBusInterface>
#include <QObject>
#include <QDebug>

#include "../dbus/dbus.hpp"

class BtPair : public QObject {
    Q_OBJECT
public:
    BtPair();
    ~BtPair();

    void pair(QString address);
};

#endif