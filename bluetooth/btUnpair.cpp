#include "../headers/bt/btUnpair.hpp"

BtUnpair::BtUnpair() {}
BtUnpair::~BtUnpair() {}

void BtUnpair::executeMethod(QVariant bluezAddress){
    DBus dbus;
    QVariantList addressList;
    addressList.append(bluezAddress.toString());
    QDBusInterface *adapterIface = dbus.createDBusInterface("org.bluez", "org/bluez/hci0", "org.bluez.Adapter1", QDBusConnection::systemBus());
    QDBusReply<void> r = dbus.callDBusMethod(adapterIface, "RemoveDevice", addressList);
    if(r.isValid()){
        qDebug() << "Paired?";
    }else{
        qDebug() << "Pairing error:" << r.error();
    }
}