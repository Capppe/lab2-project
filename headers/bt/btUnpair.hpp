#ifndef BTUNPAIR_HPP
#define BTUNPAIR_HPP

#include <QDBusInterface>
#include <QObject>
#include <QDebug>

#include "../dbus/dbus.hpp"
#include "btAbstractClass.hpp"

class BtUnpair : public BtAbstractClass {
    Q_OBJECT
public:
    BtUnpair();
    ~BtUnpair();

    void executeMethod(QVariant address) override;
};

#endif