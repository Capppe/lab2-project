#ifndef MEDIACONTROL_HPP
#define MEDIACONTROL_HPP

#include "../btAbstractClass.hpp"

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

private:
    DBus dbus;
    QDBusInterface *iface;
};

#endif