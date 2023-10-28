#ifndef BTABSTRACTCLASS_HPP
#define BTABSTRACTCLASS_HPP

#include <QObject>
#include <QVariant>
#include "../dbus/dbus.hpp"

class BtAbstractClass : public QObject
{
    Q_OBJECT

public:
    virtual void executeMethod(QVariant arg) = 0;
};

#endif