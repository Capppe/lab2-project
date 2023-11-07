#include "../../headers/bt/music/mediaControl.hpp"

MediaPlayer::MediaPlayer(QString bluezPath) 
{
    executeMethod(bluezPath);
}
MediaPlayer::~MediaPlayer() {}

void MediaPlayer::executeMethod(QVariant arg){
    iface = dbus.createDBusInterface("org.bluez", arg.toString(), "org.bluez.MediaPlayer1", QDBusConnection::systemBus());
}

void MediaPlayer::playPause(){
    if(!iface){
        return;
    }
    QVariant status = iface->property("Status");
    if(status == "paused"){
        dbus.callDBusMethod(iface, "Play");
    }else if(status == "playing"){
        dbus.callDBusMethod(iface, "Pause");
    }
}

void MediaPlayer::next(){
    dbus.callDBusMethod(iface, "Next");
}

void MediaPlayer::previous(){
    dbus.callDBusMethod(iface, "Previous");
}

QMap<QString, QVariant> MediaPlayer::getTrackInfo(){
    QMap<QString, QVariant> map;
    BtConnectedDevices connDevs;

    QStringList devs = connDevs.getConnectedDevices();

    QVariant trackInfo = dbus.callDBusProperties("org.bluez", devs.last(), "Track", "Get", "org.bluez.MediaPlayer1");
    const QDBusArgument &arg = trackInfo.value<QDBusArgument>();
    arg >> map;
    return map;
}