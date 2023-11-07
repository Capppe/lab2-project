#ifndef BTDEVICELISTENER_HPP
#define BTDEVICELISTENER_HPP

#include <QDBusObjectPath>
#include <QDBusConnection>
#include <QDBusArgument>
#include <QVariantMap>
#include <QStringList>
#include <QObject>
#include <QDebug>
#include <QMap>

class BtDeviceListener : public QObject
{
    Q_OBJECT
public:
    static BtDeviceListener *getInstance();

    void addDeviceListener(QString path);

private:
    BtDeviceListener();
    ~BtDeviceListener();
    static BtDeviceListener *instance;

public slots:
    void deviceFound(const QDBusObjectPath &objectPath, const QVariantMap &properties);
    void propertiesChanged(const QString &string, QVariantMap map, const QStringList &list);

signals:
    void device(QString path);
    void deviceConnected();
    void deviceDisconnected();
    void devicePaired();
    void playerStatus(QString status);
    void position(qint64 pos);
    void track(QVariantMap track);
};

#endif
