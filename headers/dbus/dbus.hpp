#ifndef DBUS_HPP
#define DBUS_HPP

#include <QDBusConnection>
#include <QDBusInterface>
#include <QVariantList>
#include <QDBusReply>
#include <QVariant>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QList>

class DBus : public QObject
{
    Q_OBJECT
public:
    DBus();
    ~DBus();

    QDBusInterface *createDBusInterface(const QString &service, const QString &path, const QString &interface, const QDBusConnection &connection = QDBusConnection::systemBus());
    QDBusReply<void> callDBusMethod(QDBusInterface *iface, const QString &method, QList<QVariant> argList = QList<QVariant>());
    QVariant callDBusProperties(QString service, QString path, QString name, QString method, QString iface);

    //Tools
    QString createDBusPath(QString str);
    QString parseDBusPath(QString dbusPath);
};

#endif