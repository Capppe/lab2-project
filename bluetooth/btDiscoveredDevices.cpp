#include "../headers/bt/btDiscoveredDevices.hpp"

BtDiscoveredDevices::BtDiscoveredDevices() {}
BtDiscoveredDevices::~BtDiscoveredDevices() {}

QStringList BtDiscoveredDevices::getDiscoveredDevices(){
    DBus dbus;
    QDBusInterface *iface = dbus.createDBusInterface("org.bluez", "/", "org.freedesktop.DBus.ObjectManager", QDBusConnection::systemBus());
    QDBusMessage reply = iface->call("GetManagedObjects");

    QMap<QString, QMap<QString, QVariant>> outerMap;
    QMap<QString, QVariant> innerMap;
    QStringList managedObjects;
    const QDBusArgument &dbusArg = reply.arguments().at(0).value<QDBusArgument>();
    
    dbusArg >> outerMap;
    for(QString k : outerMap.keys()){
        if(k != "/org/bluez" && k != "/org/bluez/hci0"){
            managedObjects.append(k);
        }
        innerMap = outerMap.value(k);
        for(const QString &innerKey : innerMap.keys()){
        }
    }
    qDebug() << "Strlist: " << managedObjects;
}