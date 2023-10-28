#include "../headers/dbus/dbus.hpp"

DBus::DBus() {}
DBus::~DBus() {}

QDBusInterface *DBus::createDBusInterface(const QString &service, const QString &path, const QString &interface, const QDBusConnection &connection){
    QDBusInterface *iface = new QDBusInterface(service, path, interface, connection);

    return iface->isValid() == true ? iface : nullptr;
}

QDBusReply<void> DBus::callDBusMethod(QDBusInterface *iface, const QString &method, QVariantList argList)
{
    QDBusReply<void> reply;
    if(!iface){
        qDebug() << "IFACE INVALID - METHOD:" << method;
        return reply;
    }
    if(!argList.isEmpty()){
        iface->callWithArgumentList(QDBus::AutoDetect, method, argList);
    }else{
        qDebug() << "Arglist empty, method: " << method;
        reply = iface->call(method);
    }
    if(reply.isValid()){
        // qDebug() << "Calling method " << method << "on interface" << iface.objectName() << "SUCCESS";
        return reply;
    }else{
        qDebug() << reply.error();
        return reply.error();
    }
}

QVariant DBus::callDBusProperties(QString service, QString path, QString name, QString method, QString iface){
    QDBusInterface *props = createDBusInterface(service, path, "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
    QDBusReply<QVariant> reply = props->call(method, iface, name);
    if(reply.isValid()){
        return reply.value();
    }else{
        qDebug() << "Error calling method " << method << name << "on interface" << iface << ":" << reply.error();
        return "null";
    }
}

QString DBus::createDBusPath(QString str){
    return "/org/bluez/hci0/dev_" + str.replace(QRegExp(":"),"_");
}

QString DBus::parseDBusPath(QString dbusPath){
    return dbusPath.replace("/org/bluez/hci0/dev_", "").replace(QRegExp("_"), ":");
}