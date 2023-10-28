#ifndef BTSCAN_HPP
#define BTSCAN_HPP

#include <QDBusInterface>
#include <QDBusReply>
#include <QObject>
#include <QDebug>

#include "../dbus/dbus.hpp"

class BtScanner : public QObject {
    Q_OBJECT

public:
    BtScanner();
    ~BtScanner();

    void scan();
    void stopScan();
    bool isScanning();

private:
    DBus dbus;
    QDBusInterface *adapterIface;

signals:
    void scanStarted(bool status);
    void scanStopped(bool status);
};

#endif