#ifndef BLUETOOTHINTERFACE_HPP
#define BLUETOOTHINTERFACE_HPP

#include <QWidget>
#include <QStackedWidget>
#include <QObject>
#include <QDebug>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QSettings>
#include <QDir>
#include <QList>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QBluetoothDeviceInfo>
#include <QBluetoothSocket>

#include "../customWidgets/btDevice.hpp"
#include "../customWidgets/settingsRow.hpp"
#include "bluetooth.hpp"

class BluetoothInterface : public QWidget
{
    Q_OBJECT

public:
    BluetoothInterface();
    ~BluetoothInterface();

    void addNewDevices(const QBluetoothDeviceInfo &deviceInfo);
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

signals:
    void pairedDeviceUpdate();

};

#endif