#ifndef GETSTATUS_HPP
#define GETSTATUS_HPP

#include <QDBusInterface>
#include <QDBusReply>
#include <QVariant>
#include <QObject>
#include <QString>

#include "../../dbus/dbus.hpp"
#include "playerPath.hpp"
#include "../btAbstractClass.hpp"

class MusicStatus : public BtAbstractClass
{
    Q_OBJECT

public:
    MusicStatus();
    ~MusicStatus();

    void executeMethod(QVariant bluezAddress) override;

private:
    DBus dbus;

signals:
    void status(QString status);
};

#endif