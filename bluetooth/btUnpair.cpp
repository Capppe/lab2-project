#include "../headers/bt/btUnpair.hpp"

BtUnpair::BtUnpair() {}
BtUnpair::~BtUnpair() {}

void BtUnpair::executeMethod(QVariant bluezAddress){
    DBus dbus;
    qDebug() << "Trying to remove: " << bluezAddress.toString();
    QVariantList addressList;
    QDBusObjectPath oPath = QDBusObjectPath(bluezAddress.toString());
    addressList.append(QDBusObjectPath(bluezAddress.toString()).path());
    QDBusInterface *adapterIface = dbus.createDBusInterface("org.bluez", "/org/bluez/hci0", "org.bluez.Adapter1", QDBusConnection::systemBus());
    QDBusReply<void> r = dbus.callDBusMethod(adapterIface, "RemoveDevice", addressList);
    if(r.isValid()){
        qDebug() << "Removed?";
    }else{
        qDebug() << "Removal error:" << r.error();
    }
}