#ifndef BLUETOOTHINTERFACE_HPP
#define BLUETOOTHINTERFACE_HPP

#include <QBluetoothDeviceInfo>
#include <QBluetoothSocket>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QSettings>
#include <QWidget>
#include <QObject>
#include <QThread>
#include <QLayout>
#include <QLabel>
#include <QMovie>
#include <QList>
#include <QDir>

#include "../customWidgets/settingsRow.hpp"
#include "../customWidgets/btDevice.hpp"
#include "../headers/dbus/dbus.hpp"
#include "../headers/bt/btDiscoveredDevices.hpp"
#include "../headers/bt/btDeviceListener.hpp"
#include "../headers/bt/btAbstractClass.hpp"
#include "../headers/bt/btDisconnect.hpp"
#include "../headers/bt/btConnect.hpp"
#include "../headers/bt/btUnpair.hpp"
#include "../headers/bt/btScan.hpp"
#include "../headers/bt/btPair.hpp"
#include "../headers/bt/music/playerPath.hpp"
#include "bluetooth.hpp"

class BluetoothInterface : public QWidget
{
    Q_OBJECT

public:
    BluetoothInterface();
    ~BluetoothInterface();

    void addNewDevices(QString devPath);
    void addNewDevicesToLayout();

private:
    void bindButtons();
    void bindSignals();
    void initVars();
    void populateLayouts();
    void populateWidgets();
    void styleLayout();

    void removeKnownDevice();
    void bindDeviceSignals(BtDevice *device);
    void addConnectedDevice(BtDevice *device);
    void addKnownDevices();

    void setActiveButton(QPushButton *activeButton);
    void setSearching(const bool &visible);

    void createSignal(BtAbstractClass *cls, QString arg = QString());

    void createSettings();

    QVBoxLayout *scrollAreaLayout;
    QVBoxLayout *searchLayout;
    QVBoxLayout *mainLayout;
    QVBoxLayout *containerLayout;
    QVBoxLayout *settingsLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *devicesLayout;
    QVBoxLayout *searchingLabelLayout;

    QStackedWidget *stackedWidget;
    QScrollArea *mainScrollArea;
    QScrollArea *searchScrollArea;
    QScrollArea *settingsScrollArea;

    QWidget *deviceScrollContent;
    QWidget *searchScrollContent;
    QWidget *settingsScrollContent;
    QWidget *containerWidget;

    QPushButton *search;
    QPushButton *settings;
    QPushButton *devices;

    QList<BtDevice*> *deviceList;
    QList<BtDevice*> *knownDeviceList;

    Bluetooth *bt;
    QLabel *searchGifLabel;
    
    //BtDeviceListener *listener;
    QThread *workerThread;
    DBus *dbus;
    QString *dbusPath;
    BtConnect *c;
    BtUnpair *btUnpair;
    BtScanner *btScanner;
    BtDisconnect *btDisc;

    PlayerPath *pPath;

signals:
    void pairedDeviceUpdate();

};

#endif
