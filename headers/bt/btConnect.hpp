#ifndef BTCONNECT_HPP
#define BTCONNECT_HPP

#include <QDBusInterface>
#include <QObject>
#include <QDebug>

#include "../dbus/dbus.hpp"
#include "btAbstractClass.hpp"

class BtConnect : public BtAbstractClass {
    Q_OBJECT
public:
    BtConnect();
    ~BtConnect();

    void executeMethod(QVariant address) override;
private:
    DBus dbus;
};

#endif