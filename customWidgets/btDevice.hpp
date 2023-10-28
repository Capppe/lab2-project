#ifndef BTDEVICE_HPP
#define BTDEVICE_HPP

#include <QAbstractButton>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QCheckBox>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <QIcon>
#include <QDir>

#include "../headers/bt/btDeviceListener.hpp"

class BtDevice : public QWidget
{
    Q_OBJECT

public:
    BtDevice(const QString name, const QString address, QWidget *parent);
    BtDevice();
    ~BtDevice();
    
    QString getAddress() const;
    QString getName() const;

    void setOnPaired();
    void setOnConnecting();
    void setOnDisconnecting();
    void setOnDisconnected();

    QPushButton *connectButton;
    QPushButton *pairButton;

public slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onRemoveButtonClicked();
    void setOnConnected();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private: 
    void setStyling();
    void addLayouts();
    void bindButtons();
    void bindSignals();
    QPixmap getDeviceIcon(int device);

    QVBoxLayout *mainLayout;
    QHBoxLayout *visibleLayout;
    QHBoxLayout *hiddenLayout;
    QVBoxLayout *devInfoLayout;
    
    //Visible widgets
    QPixmap deviceIconPixmap;
    QPixmap deleteIconPixmap;
    QLabel *deviceIcon;
    QLabel *name;
    QLabel *address;
    QLabel *statusLabel;
    QWidget *containerWidget;
    QWidget *expanderWidget;
    QWidget *devInfoWidget;
    QPushButton *deleteButton;

    //Hidden widgets
    QWidget *hiddenLayoutContainer;
    QCheckBox *autoConnCheck;

signals:
    void connectButtonClicked(const QString &address);
    void disconnectButtonClicked(const QString &address);
    void removeButtonClicked(const QString &address);
};

#endif