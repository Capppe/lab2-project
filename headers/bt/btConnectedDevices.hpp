#ifndef BTCONNECTEDDEVICE_HPP
#define BTCONNECTEDDEVICE_HPP

#include <QDBusInterface>
#include <QDBusArgument>
#include <QStringList>
#include <QObject>
#include <QDebug>

#include "../dbus/dbus.hpp"
#include "btDiscoveredDevices.hpp"
#include "btAbstractClass.hpp"

class BtConnectedDevices : public BtAbstractClass {
    Q_OBJECT
public:
    BtConnectedDevices();
    ~BtConnectedDevices();

    void executeMethod(QVariant arg) override;
    QStringList getConnectedDevices();
private:
    DBus dbus;
    BtDiscoveredDevices discDevs;
};

#endif