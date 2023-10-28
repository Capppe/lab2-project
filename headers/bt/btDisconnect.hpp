#ifndef BTDISCONNECT_HPP
#define BTDISCONNECT_HPP

#include <QDBusInterface>
#include <QObject>
#include <QDebug>

#include "../dbus/dbus.hpp"
#include "btAbstractClass.hpp"

class BtDisconnect : public BtAbstractClass{
    Q_OBJECT
public:
    BtDisconnect();
    ~BtDisconnect();

    void executeMethod(QVariant address) override;

private:
    DBus dbus;
};

#endif