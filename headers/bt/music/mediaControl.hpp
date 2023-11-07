#ifndef MEDIACONTROL_HPP
#define MEDIACONTROL_HPP

#include <QMap>

#include "../btAbstractClass.hpp"
#include "../btConnectedDevices.hpp"

class MediaPlayer : BtAbstractClass
{
    Q_OBJECT

public:
    MediaPlayer(QString bluezPath);
    ~MediaPlayer();
    void executeMethod(QVariant arg) override;

    void playPause();
    void next();
    void previous();

    QMap<QString, QVariant> getTrackInfo();

private:
    DBus dbus;
    QDBusInterface *iface;
};

#endif