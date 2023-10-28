#include "../headers/bt/btPair.hpp"

BtPair::BtPair() {}
BtPair::~BtPair() {}

void BtPair::pair(QString bluezAddress){
    DBus dbus;
    QDBusInterface *adapterIface = dbus.createDBusInterface("org.bluez", bluezAddress, "org.bluez.Device1", QDBusConnection::systemBus());
    QDBusReply<void> r = dbus.callDBusMethod(adapterIface, "Pair");
    if(r.isValid()){
        qDebug() << "Paired?";
    }else{
        qDebug() << "Pairing error:" << r.error();
    }
}
