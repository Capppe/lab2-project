#include "../../headers/bt/music/status.hpp"

MusicStatus::MusicStatus() {}
MusicStatus::~MusicStatus() {}

void MusicStatus::executeMethod(QVariant bluezAddress){
    PlayerPath pPath;
    QVariant *r = new QVariant;

    pPath.executeMethod(bluezAddress);

    QObject::connect(&pPath, &PlayerPath::path, this, [&](QString path){
        QDBusInterface *playerIface = dbus.createDBusInterface("org.bluez", path, "org.bluez.MediaPlayer1", QDBusConnection::systemBus());
        QVariant status = playerIface->property("Status");

        emit(status.toString());
    });
}