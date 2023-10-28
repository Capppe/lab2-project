#include "../headers/bt/btConnect.hpp"
#include <thread>

BtConnect::BtConnect() {}
BtConnect::~BtConnect() {}

void BtConnect::executeMethod(QVariant bluezAddress){
    QDBusInterface *adapterIface = dbus.createDBusInterface("org.bluez", bluezAddress.toString(), "org.bluez.Device1", QDBusConnection::systemBus());
    if(adapterIface == nullptr){
        qDebug() << "IFACE = NULL, bluezAddrress: " << bluezAddress;
        return;
    }
        qDebug() << "IFACE NOT NULL, bluezAddrress: " << bluezAddress;
    QDBusReply<void> r = dbus.callDBusMethod(adapterIface, "Connect");

    if(r.isValid()){
        qDebug() << "Connected?";
    }else{
        qDebug() << "Connection error:" << r.error();
        return;
    }
}