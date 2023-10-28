#ifndef BTDISCOVEREDDEVICES_HPP
#define BTDISCOVEREDDEVICES_HPP

#include <QDBusInterface>
#include <QDBusObjectPath>
#include <QDBusMessage>
#include <QObject>
#include <QDebug>
#include <QMap>

#include "../dbus/dbus.hpp"

class BtDiscoveredDevices : public QObject {
    Q_OBJECT
public:
    BtDiscoveredDevices();
    ~BtDiscoveredDevices();

    QStringList getDiscoveredDevices();
};

#endif