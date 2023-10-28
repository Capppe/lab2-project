#include "../headers/bt/btDisconnect.hpp"

BtDisconnect::BtDisconnect() {}
BtDisconnect::~BtDisconnect() {}

void BtDisconnect::executeMethod(QVariant bluezAddress){
    qDebug() << "BLUEZADDRESS - DISCONNECT: " << bluezAddress.toString();
    QDBusInterface *adapterIface = dbus.createDBusInterface("org.bluez", bluezAddress.toString(), "org.bluez.Device1", QDBusConnection::systemBus());
    QDBusReply<void> r = dbus.callDBusMethod(adapterIface, "Disconnect");
    if(r.isValid()){
        qDebug() << "Disconnected?";
    }else{
        qDebug() << "Disconnection error:" << r.error();
    }
}