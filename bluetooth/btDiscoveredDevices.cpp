#include "../headers/bt/btDiscoveredDevices.hpp"

BtDiscoveredDevices::BtDiscoveredDevices() {}
BtDiscoveredDevices::~BtDiscoveredDevices() {}

QMap<QString, QMap<QString, QMap<QString, QVariant>>> BtDiscoveredDevices::getDiscoveredDevices(int type){
    DBus dbus;
    QDBusInterface *iface = dbus.createDBusInterface("org.bluez", "/", "org.freedesktop.DBus.ObjectManager", QDBusConnection::systemBus());
    QDBusMessage reply = iface->call("GetManagedObjects");

    QMap<QString, QMap<QString, QMap<QString, QVariant>>> outerMap;
    const QDBusArgument &dbusArg = reply.arguments().at(0).value<QDBusArgument>();
    
    dbusArg >> outerMap;

    return outerMap;
}