#include "../headers/bt/btScan.hpp"

BtScanner::BtScanner() 
{
    adapterIface = dbus.createDBusInterface("org.bluez", "/org/bluez/hci0", "org.bluez.Adapter1", QDBusConnection::systemBus());
}
BtScanner::~BtScanner() {}

void BtScanner::scan(){
    QDBusReply<void> r = dbus.callDBusMethod(adapterIface, "StartDiscovery");
    if(r.isValid()){
        qDebug() << "Scanning";
        emit(scanStarted(true));
    }else{
        qDebug() << "Scan error:" << r.error();
    }
}

void BtScanner::stopScan(){
    QDBusReply<void> r = dbus.callDBusMethod(adapterIface, "StopDiscovery");
    if(r.isValid()){
        qDebug() << "Stopping scanning";
        emit(scanStopped(false));
    }else{
        qDebug() << "Stop scan error:" << r.error();
    }
}

bool BtScanner::isScanning(){
    QVariant r = adapterIface->property("Discoverable");
    if(r.isValid()){
        qDebug() << "Discoverable: " << r.toBool();
    }else{
        qDebug() << "Discoverable: " << r.toBool();
    }
}
