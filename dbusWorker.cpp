#include "headers/dbusWorker.hpp"

DBusWorker::DBusWorker(QObject *parent) : QObject(parent)
{

}

void DBusWorker::operate(){
    while(true){
        QString path = Bluetooth::getInstance()->getPlayerPath();
        QDBusInterface mediaProps("org.bluez", path, "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
        if(mediaProps.isValid()){
            QDBusReply<QVariant> reply = mediaProps.call("Get", "org.bluez.MediaPlayer1", "Position");

            if (reply.isValid()) {
                QVariant r = reply.value();
                emit result(r.toInt());
            }else{
                qDebug() << reply.error();
                emit error("DBus call failed");
            }
        }
        QThread::sleep(1);
    }
}