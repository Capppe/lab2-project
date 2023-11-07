#ifndef BTDISCOVEREDDEVICES_HPP
#define BTDISCOVEREDDEVICES_HPP

#include <QDBusInterface>
#include <QDBusObjectPath>
#include <QDBusMessage>
#include <QVariant>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>

#include "../dbus/dbus.hpp"

class BtDiscoveredDevices : public QObject {
    Q_OBJECT
public:
    BtDiscoveredDevices();
    ~BtDiscoveredDevices();

    QMap<QString, QMap<QString, QMap<QString, QVariant>>> getDiscoveredDevices(int type);
};

#endif