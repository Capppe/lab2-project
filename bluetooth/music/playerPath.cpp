#include "../../headers/bt/music/playerPath.hpp"

PlayerPath::PlayerPath() {}
PlayerPath::~PlayerPath() {}

void PlayerPath::executeMethod(QVariant bluezAddress){
    QDBusInterface *iface = dbus.createDBusInterface("org.bluez", bluezAddress.toString(), "org.bluez.MediaControl1", QDBusConnection::systemBus());
    QVariant r = iface->property("Player");

    if(r.isValid()){
        qDebug() << "Player: " << r.toString();
        emit(path(r.toString()));
    }else{
        qDebug() << "Player not found";
    }
}