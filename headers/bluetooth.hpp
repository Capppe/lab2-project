#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP

#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceInfo>
#include <QBluetoothAddress>
#include <QDBusArgument>
#include <QSettings>
#include <QMetaType>
#include <QProcess>
#include <QString>
#include <cstdlib>
#include <thread>
#include <QtDBus>
#include <QDebug>
#include <QList>
#include <QPair>
#include <QSet>


class Bluetooth : public QObject
{
    Q_OBJECT
public:
    static Bluetooth *getInstance();

    void checkLocalDevice();
    void scan();
    void stopScan();
    void pairAndConnect(const QString &address, const QString &name);
    void disconnect(const QString &address);
    void unpair(const QString &address);

    void mPlay();
    void mPause();
    void mStop();
    void mSkip();
    void mRewind();
    void mPrev();
    int mGetPosition();

    QString createBluezPath(QString address = nullptr);
    QString getPlayerPath();
    
    QDBusInterface getDBusInterface();
    QMap<QString, QString> getSettings();
    QList<QBluetoothAddress> getCurrentDevices();

    void setSettings();
    void setAutoConnectDevice(const QBluetoothAddress &address);
    void setAutoOpenMusic(bool autoOpen);
    void setBluetoothNotifications(bool blueNotif);
    void setDeviceName(const QString &devName);

    QString getBtMusicStatus();
    QMap<QString, QVariant> getBtCurrMusicInfo();
    int getBtSongPos();
    void tester(QString str, QVariantMap map, QStringList strList);
    
private:
    Bluetooth();
    ~Bluetooth();

    QDBusReply<QVariant> mDBusCommand(int type);


    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;

    QSet<QString> discoveredAddresses;
    QList<QPair<QString, QString>> pairedDevices;

    // Settings
    QBluetoothAddress autoConnectDevice;
    bool autoOpen;
    bool blueNotif;
    QString devName;

    static Bluetooth *instance;

private slots:
    void onDeviceDiscovered(const QBluetoothDeviceInfo &deviceInfo);
    void onScanFinished();
    void onDeviceConnected(const QBluetoothAddress &address);
    void onDeviceDisconnected(const QBluetoothAddress &address);

signals:
    void scanStatus(const bool &visible);
    void deviceDiscovered(const QBluetoothDeviceInfo &deviceInfo);
    void deviceConnecting(const QBluetoothAddress &address);
    void deviceConnected(const QString &status, const QBluetoothAddress &address);
    void deviceDisconnecting(const QBluetoothAddress &address);
    void deviceDisconnected(const QString &status, const QBluetoothAddress &address);
};

#endif