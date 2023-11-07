#ifndef PLAYERPATH_HPP
#define PLAYERPATH_HPP

#include <QDBusObjectPath>

#include "../btAbstractClass.hpp"

class PlayerPath : public BtAbstractClass
{
    Q_OBJECT
public:
    PlayerPath();
    ~PlayerPath();
    
    void executeMethod(QVariant bluezAddress) override;

private:
    DBus dbus;

signals:
    void path(QString path);
};

#endif