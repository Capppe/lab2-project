#include "headers/bluetoothInterface.hpp"
#include "headers/dataStorage.hpp"

BluetoothInterface::BluetoothInterface() 
{
    this->initVars();
    this->populateLayouts();
    this->populateWidgets();
    this->styleLayout();
    this->bindButtons();
    this->bindSignals();
    this->addKnownDevices();
    this->createSettings();
    qDebug() << "BluetoothInterface created";
}

BluetoothInterface::~BluetoothInterface() 
{
    qDebug() << "BluetoothInterface destroyed";
    bt->stopScan();
}

void BluetoothInterface::bindButtons(){
    QObject::connect(devices, &QPushButton::clicked, this, [&](){
        this->setActiveButton(devices);
        stackedWidget->setCurrentIndex(0);
    });
    QObject::connect(search, &QPushButton::clicked, this, [&](){
        this->setActiveButton(search);
        stackedWidget->setCurrentIndex(1);
        bt->scan();
    });
    QObject::connect(settings, &QPushButton::clicked, this, [&](){
        this->setActiveButton(settings);
        stackedWidget->setCurrentIndex(2);
    });
}

void BluetoothInterface::bindSignals(){
    QObject::connect(this, &BluetoothInterface::pairedDeviceUpdate, this, [&](){
        QString amount = QString::number(DataStorage::readBtDevices().size());
        this->devices->setText("Devices(" + amount + ")");
    });

    QObject::connect(bt, &Bluetooth::deviceDiscovered, this, &BluetoothInterface::addNewDevices);
    QObject::connect(bt, &Bluetooth::scanStatus, this, &BluetoothInterface::setSearching);
}

// Ui-init
void BluetoothInterface::initVars(){
    bt = Bluetooth::getInstance();
    searchGifLabel = new QLabel(this);

    mainLayout = new QVBoxLayout(this);
    containerLayout = new QVBoxLayout();
    containerWidget = new QWidget();
    buttonLayout = new QHBoxLayout();

    mainScrollArea = new QScrollArea();
    deviceScrollContent = new QWidget(mainScrollArea);
    scrollAreaLayout = new QVBoxLayout(deviceScrollContent);

    searchScrollArea = new QScrollArea();
    searchScrollContent = new QWidget(searchScrollArea);
    searchLayout = new QVBoxLayout(searchScrollContent);

    settingsScrollArea = new QScrollArea();
    settingsScrollContent = new QWidget(settingsScrollArea);
    settingsLayout = new QVBoxLayout(settingsScrollContent);

    stackedWidget = new QStackedWidget(containerWidget);

    deviceList = new QList<BtDevice*>;
    knownDeviceList = new QList<BtDevice*>;

    devices = new QPushButton("Devices(0)");
    search = new QPushButton("Search");
    settings = new QPushButton("Settings");
}

void BluetoothInterface::populateLayouts(){
    mainScrollArea->setWidget(deviceScrollContent);
    deviceScrollContent->setLayout(scrollAreaLayout);

    searchScrollArea->setWidget(searchScrollContent);
    searchScrollContent->setLayout(searchLayout);

    settingsScrollArea->setWidget(settingsScrollContent);
    settingsScrollContent->setLayout(settingsLayout);

    // searchingLabelLayout->addWidget(searchGifLabel);

    stackedWidget->addWidget(mainScrollArea);
    stackedWidget->addWidget(searchScrollArea);
    stackedWidget->addWidget(settingsScrollArea);
    stackedWidget->setCurrentIndex(0);

    buttonLayout->addWidget(devices);
    buttonLayout->addWidget(search);
    buttonLayout->addWidget(settings);
    
    searchLayout->addWidget(searchGifLabel, 0 ,Qt::AlignBottom);

    containerLayout->addWidget(stackedWidget);
    containerLayout->addLayout(buttonLayout);

    mainLayout->addLayout(containerLayout);
}

void BluetoothInterface::populateWidgets(){
    searchGifLabel->setText("Searching...");
    searchGifLabel->setVisible(false);
}

void BluetoothInterface::styleLayout(){
    scrollAreaLayout->setAlignment(Qt::AlignTop);
    searchLayout->setAlignment(Qt::AlignTop);
    settingsLayout->setAlignment(Qt::AlignTop);

    mainScrollArea->setWidgetResizable(true);
    searchScrollArea->setWidgetResizable(true);
    settingsScrollArea->setWidgetResizable(true);

    searchScrollContent->setObjectName("scrollContent");
    deviceScrollContent->setObjectName("scrollContent");
    settingsScrollContent->setObjectName("scrollContent");

    devices->setMinimumHeight(100);
    search->setMinimumHeight(100);
    settings->setMinimumHeight(100);

    searchGifLabel->setMaximumHeight(50);
    searchGifLabel->setAlignment(Qt::AlignCenter);
    searchGifLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    this->setActiveButton(devices);
    this->setStyleSheet(
        "#containerWidget{ background-color: black; } \
        QPushButton{ font: 20px; } \
        QLabel{ color: white; font: 16px; } \
        QScrollArea{ background: transparent; border: 1px solid black; border-radius: 10px; } \
        #btDevice{ background-color: black; } \
        #scrollContent{ background-color: transparent; border: 1px solid black; border-radius: 10px; }"
    );
}

void BluetoothInterface::setActiveButton(QPushButton *activeButton){
    devices->setStyleSheet("");
    search->setStyleSheet("");
    settings->setStyleSheet("");
    activeButton->setStyleSheet("QPushButton{ border: 1px solid green; color: green; background-color: #070707; }");
}

//Functionality
void BluetoothInterface::addKnownDevices(){
    QList<QPair<QString, QString>> knownDevices = DataStorage::readBtDevices();
    if(knownDevices.isEmpty()){
        return;
    }

    for(const auto &device : knownDevices){
        BtDevice *knownDevice = new BtDevice(device.first, device.second, nullptr);
        knownDeviceList->append(knownDevice);
        deviceList->append(knownDevice);
        scrollAreaLayout->addWidget(knownDevice);
        bindDeviceSignals(knownDevice);
        knownDevice->setOnPaired();
        emit(this->pairedDeviceUpdate());
    }
}

void BluetoothInterface::addNewDevices(const QBluetoothDeviceInfo &deviceInfo){
    QList<QBluetoothAddress> currentDevices = bt->getCurrentDevices();
    if(currentDevices.contains(deviceInfo.address())){
        return;
    }
    BtDevice *btDevice = new BtDevice(deviceInfo.name(), deviceInfo.address().toString(), nullptr);
    searchLayout->insertWidget(searchLayout->count()-1, btDevice);
    deviceList->append(btDevice);
    bindDeviceSignals(btDevice);
}

void BluetoothInterface::addConnectedDevice(BtDevice *device){
    scrollAreaLayout->addWidget(device);
    knownDeviceList->append(device);
    device->setOnPaired();
    emit(this->pairedDeviceUpdate());
}

void BluetoothInterface::removeKnownDevice(){
    for(const auto &device : *knownDeviceList){
        if(scrollAreaLayout->indexOf(device) != -1){
            scrollAreaLayout->removeWidget(device);
            device->deleteLater();
        }else{
            qDebug() << "Removal error!" << scrollAreaLayout->indexOf(device) << searchLayout->indexOf(device);
        }
    }
}

void BluetoothInterface::bindDeviceSignals(BtDevice *device){
    QObject::connect(device, &BtDevice::connectButtonClicked, bt, [&](const QString &address, const QString &name){
        bt->pairAndConnect(address, name);
    });

    QObject::connect(device, &BtDevice::disconnectButtonClicked, bt, [&](const QString &address){
        bt->disconnect(address);
    });

    QObject::connect(device, &BtDevice::removeButtonClicked, bt, [&](const QString &address){
        removeKnownDevice();
        bt->unpair(address);
        bt->disconnect(address);
        DataStorage::removeBtDevice(address);
        emit(this->pairedDeviceUpdate());
    });

    QObject::connect(bt, &Bluetooth::deviceConnected, [&](const QString &status, const QBluetoothAddress &address){
        for(BtDevice *device : *deviceList){
            if(device->getAddress() == address.toString()){
                device->setOnConnected();
                addConnectedDevice(device);
                searchLayout->removeWidget(device);
            }
        }
    });

    QObject::connect(bt, &Bluetooth::deviceDisconnected, [&](const QString &status, const QBluetoothAddress &address){
        for(BtDevice *device : *deviceList){
            if(device->getAddress() == address.toString()){
                device->setOnDisconnected();
            }
        }
    });

    QObject::connect(bt, &Bluetooth::deviceConnecting, [&](const QBluetoothAddress &address){
        for(BtDevice *device : *deviceList){
            if(device->getAddress() == address.toString()){
                device->setOnConnecting();
            }
        }
    });

    QObject::connect(bt, &Bluetooth::deviceDisconnecting, [&](const QBluetoothAddress &address){
        for(BtDevice *device : *deviceList){
            if(device->getAddress() == address.toString()){
                device->setOnDisconnecting();
            }
        }
    });
}

void BluetoothInterface::setSearching(const bool &visible){
    searchGifLabel->setVisible(visible);
}

void BluetoothInterface::createSettings(){
    QSettings settings;
    QList<SettingsRow*> settingsList;
    settings.beginGroup("Bluetooth");
    settings.beginGroup("General");

        QString autoConnectAddr = settings.value("autoConnectTo").toString();
        QString localName = settings.value("localDeviceName").toString();
        bool openMusic = settings.value("openMusicOnConnection").toBool();
        bool enableNotif = settings.value("enableBluetoothNotifications").toBool();

        SettingsRow *header = new SettingsRow("General", nullptr);
        SettingsRow *autoConnectSetting = new SettingsRow("Auto Connect", "Device address to auto connect on start", nullptr);
        SettingsRow *localNameSetting = new SettingsRow("Local Device Name", "Name that will be visible to other devices", nullptr);
        SettingsRow *openMusicSetting = new SettingsRow("Auto Open music", "Open music upon successfully connecting to a device", nullptr);
        SettingsRow *enableNotifsSetting = new SettingsRow("Bluetooth notifications", "Enable notifications from bluetooth updates", nullptr); 
        settingsList << header << autoConnectSetting << localNameSetting << openMusicSetting << enableNotifsSetting;

        for(SettingsRow *setting : settingsList){
            settingsLayout->addWidget(setting);
        }
    settings.endGroup();
    settings.endGroup();
}