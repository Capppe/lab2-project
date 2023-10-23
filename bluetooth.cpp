#include "headers/bluetooth.hpp"
#include "headers/bluetoothInterface.hpp"
#include "headers/dataStorage.hpp"

Bluetooth *Bluetooth::instance = nullptr;

Bluetooth::Bluetooth() {
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    localDevice = new QBluetoothLocalDevice(this);
    pairedDevices = DataStorage::readBtDevices();
    checkLocalDevice();
}

Bluetooth::~Bluetooth() {}

Bluetooth *Bluetooth::getInstance(){
    if(!instance){
        instance = new Bluetooth();
    }
    return instance;
}

void Bluetooth::checkLocalDevice(){
    if(!localDevice->isValid()){
        qDebug() << "Local device invAlid";
        return;
    }

    localDevice->powerOn();    

    QObject::connect(localDevice, &QBluetoothLocalDevice::deviceConnected, this, &Bluetooth::onDeviceConnected);
    QObject::connect(localDevice, &QBluetoothLocalDevice::deviceDisconnected, this, &Bluetooth::onDeviceDisconnected);
    QObject::connect(localDevice, &QBluetoothLocalDevice::hostModeStateChanged, [&](QBluetoothLocalDevice::HostMode state) {
        qDebug() << "State: " << state;
    });

    localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
}

void Bluetooth::scan(){
    stopScan();
    qDebug() << "Starting scan";

    emit(scanStatus(true));

    QObject::connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &Bluetooth::onDeviceDiscovered);
    QObject::connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &Bluetooth::onScanFinished);

    discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::ClassicMethod);
}

void Bluetooth::stopScan(){
    QDBusInterface adapter("org.bluez", "/org/bluez/hci0", "org.bluez.Adapter1", QDBusConnection::systemBus());
    if(adapter.isValid()){
        QDBusReply<void> reply = adapter.call("StopDiscovery");
        if(reply.isValid()){
            qDebug() << "Stopping discovery/scan";
            emit(scanStatus(false));
        }else{
            qDebug() << "Stopping discovery FAILED with code:" << reply.error();
        }
    }
}

void Bluetooth::pairAndConnect(const QString &address, const QString &name){
    stopScan();

    emit(deviceConnecting(QBluetoothAddress(address)));
    QDBusConnection bus = QDBusConnection::systemBus();
    if(!bus.isConnected()){
        qDebug() << "D-Bus connection failed";
        return; // TODO add errror handler
    }
    
    QStringList arguments;
    arguments << "-c NoInputNoOutput";
    QProcess *process = new QProcess;
    process->start("/usr/bin/bt-agent", arguments);
    QString bluezAddress = createBluezPath(address);

    QDBusInterface device("org.bluez", bluezAddress, "org.bluez.Device1", bus);
    if(device.isValid()){
        QDBusReply<void> pairMsg = device.call("Pair");
        QThread::msleep(2000);
        if(pairMsg.isValid()){
            //TODO add status
        }else{
            qDebug() << "Pairing failed with code: " << pairMsg.error().message();
            //TODO add error handler
        }
        QDBusReply<void> connMsg = device.call("Connect");
        if(connMsg.isValid()){
            DataStorage::saveBtDevice(name, address);
            //TODO add status
        }else{
            qDebug() << "Connection failed with code: " << connMsg.error().message();
            //TODO add error handler
        }
        
    }else{
        qDebug() << "Invalid device";
        //TODO add error handler
    }
}

void Bluetooth::disconnect(const QString &address){
    QDBusConnection bus = QDBusConnection::systemBus();
    if(!bus.isConnected()){
        qDebug() << "D-Bus connection failed";
        return; // TODO add errror handler
    }
    emit(deviceDisconnecting(QBluetoothAddress(address)));

    QString bluezAddress = createBluezPath(address);
    QDBusInterface device("org.bluez", bluezAddress, "org.bluez.Device1", bus);

    if(device.isValid()){
        QDBusReply<void> disconnectMsg = device.call("Disconnect");
        if(disconnectMsg.isValid()){
            //TODO add status
        }else{
            qDebug() << "Disconnect failed with code: " << disconnectMsg.error().message();
            //TODO add error handler
        }
    }else{
        qDebug() << "Invalid device - DISCONNECT";
        //TODO add error handler
    }

    qDebug() << "Disconnect";
}

void Bluetooth::unpair(const QString &address){
    QDBusConnection bus = QDBusConnection::systemBus();
    if(!bus.isConnected()){
        qDebug() << "D-Bus connection failed";
        return; // TODO add errror handler
    }

    QDBusInterface adapter("org.bluez", "/org/bluez/hci0", "org.bluez.Adapter1", bus);
    if(adapter.isValid()){
        QString bluezAddress = createBluezPath(address);
        qDebug() << "ADDRESS: " << bluezAddress;
        QDBusReply<void> unpairMsg = adapter.call(QDBus::AutoDetect, "RemoveDevice", QDBusObjectPath(bluezAddress));
        // adapter.callWithArgumentList()
        if(unpairMsg.isValid()){
            auto it = std::find_if(pairedDevices.begin(), pairedDevices.end(), [address](const QPair<QString, QString>& pair) {
                return pair.second == address;
            });
        }else{
            qDebug() << "Unpair failed with code: " << unpairMsg.error();
        }
    }
}

void Bluetooth::onDeviceDiscovered(const QBluetoothDeviceInfo &deviceInfo){
    QString devAddress = deviceInfo.address().toString();

    if(!discoveredAddresses.contains(devAddress) && !pairedDevices.contains(QPair(deviceInfo.name(), devAddress))){
        emit(deviceDiscovered(deviceInfo));
        //BluetoothInterface::addNewDevices(deviceInfo);
        discoveredAddresses.insert(devAddress);
    }
}

void Bluetooth::onScanFinished(){
    emit(scanStatus(false));
}

void Bluetooth::onDeviceConnected(const QBluetoothAddress &address){
    qDebug() << "Connected to the Bluetooth device";
    emit(deviceConnected(QString("Connected"), address));
}

void Bluetooth::onDeviceDisconnected(const QBluetoothAddress &address){
    qDebug() << "Disconnected from the Bluetooth device";
    emit(deviceDisconnected(QString("Disconnected"), address));
}

QList<QBluetoothAddress> Bluetooth::getCurrentDevices(){
    return localDevice->connectedDevices();
}

// Settings



QMap<QString, QString> Bluetooth::getSettings(){
    
}

void Bluetooth::setSettings(){
    QSettings settings;

    settings.beginGroup("Bluetooth");
        settings.beginGroup("General");
            settings.setValue("autoConnectTo", QVariant(this->autoConnectDevice.toString()));
            settings.setValue("openMusicOnConnection", QVariant(this->autoOpen));
            settings.setValue("enableBluetoothNotifications", QVariant(this->blueNotif));
            settings.setValue("localDeviceName", QVariant(this->devName));
        settings.endGroup();
    settings.endGroup();
}

void Bluetooth::setAutoConnectDevice(const QBluetoothAddress &address){
    this->autoConnectDevice = address;
}

void Bluetooth::setAutoOpenMusic(bool autoOpen){
    this->autoOpen = autoOpen;
}

void Bluetooth::setBluetoothNotifications(bool blueNotif){
    this->blueNotif = blueNotif;
}

void Bluetooth::setDeviceName(const QString &devName){
    this->devName = devName;
}

QString Bluetooth::createBluezPath(QString address){
    if(address == nullptr){
        address = localDevice->connectedDevices().at(0).toString();
    }
    return "/org/bluez/hci0/dev_" + address.replace(QRegExp(":"),"_");
}

QString Bluetooth:: getPlayerPath(){
    QString bluezAddress = createBluezPath();
    QString pPath;
    QDBusInterface playerPath("org.bluez", bluezAddress, "org.bluez.MediaControl1", QDBusConnection::systemBus());
    if(playerPath.isValid()){
        QVariant r = playerPath.property("Player");

        QDBusObjectPath path = r.value<QDBusObjectPath>();
        pPath = path.path();
    }
    return pPath;
}

QString Bluetooth::getBtMusicStatus(){
    if(localDevice->connectedDevices().size() <= 0){
        return "NULL";
    }
    QString bluezAddress = createBluezPath();
    QString playerPath = getPlayerPath();

    QDBusInterface mediaProps("org.bluez", playerPath, "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
    if(mediaProps.isValid()){
        QDBusReply<QVariant> reply = mediaProps.call("Get", "org.bluez.MediaPlayer1", "Status");

        if (reply.isValid()) {
            QVariant r = reply.value();

            return r.toString();
        } else{
            qDebug() << reply.error();
        }
    }else{
        qDebug() << "Mediaprops - getBtMusicStatus() invalid";
    }
    return "NULL";
}

QMap<QString, QVariant> Bluetooth::getBtCurrMusicInfo(){
    QString bluezAddress = createBluezPath();
    QString playerPath = getPlayerPath();
    QMap<QString, QVariant> map;

    QDBusInterface mediaProps("org.bluez", playerPath, "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
    if(mediaProps.isValid()){
        QDBusMessage message = mediaProps.call("Get", "org.bluez.MediaPlayer1", "Track");

        if (message.type() == QDBusMessage::ReplyMessage) {
            QDBusVariant r = message.arguments().at(0).value<QDBusVariant>();
            QDBusArgument arg = r.variant().value<QDBusArgument>();
          
            arg >> map;
        }
    }
    return map;
}

int Bluetooth::getBtSongPos(){
    if(localDevice->connectedDevices().size() <= 0){
        return 0;
    }
    QString bluezAddress = createBluezPath();
    QString playerPath = getPlayerPath();

    QDBusInterface mediaProps("org.bluez", playerPath, "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
    if(mediaProps.isValid()){
        QDBusReply<QVariant> reply = mediaProps.call("Get", "org.bluez.MediaPlayer1", "Position");

        if (reply.isValid()) {
            QVariant r = reply.value();
            return r.toInt();
        }
    }
    return 0;
}

void Bluetooth::mPlay(){
    mDBusCommand(1);
    qDebug() << "Playing - bt";
}

void Bluetooth::mPause(){
    mDBusCommand(2);
    qDebug() << "Pausing - bt";
}

void Bluetooth::mStop(){
    mDBusCommand(3);
}

void Bluetooth::mSkip(){
    mDBusCommand(4);
}

void Bluetooth::mRewind(){
    mDBusCommand(5);
}

void Bluetooth::mPrev(){
    mDBusCommand(6);
}

int Bluetooth::mGetPosition(){
    QDBusReply<QVariant> tmp = mDBusCommand(7);
    QVariant r = tmp.value();
    return r.toInt();
}

QDBusReply<QVariant> Bluetooth::mDBusCommand(int type){
    QString playerPath = getPlayerPath();

    QDBusInterface mediaProps("org.bluez", playerPath, "org.bluez.MediaPlayer1", QDBusConnection::systemBus());
    if(mediaProps.isValid()){    
        QDBusReply<QVariant> reply;
        
        switch (type)
        {
        case 1:
            reply = mediaProps.call("Play");
            qDebug() << reply.value().toString();
            break;
        case 2:
            reply = mediaProps.call("Pause");
            break;
        case 3:
            reply = mediaProps.call("Stop");
            break;
        case 4:
            reply = mediaProps.call("Next");
            break;
        case 5:
            reply = mediaProps.call("Rewind");
            break;
        case 6:
            reply = mediaProps.call("Previous");
            break;
        case 7:
            reply = mediaProps.call("Position");
            break;
        
        default:
            break;
        }
        return reply;
    }
}

void Bluetooth::tester(QString str, QVariantMap map, QStringList strList){
    qDebug() << "STR: " << str;

    for (const QString& key : map.keys()) {
        qDebug() << "Key: " << key << ", Value: " << map.value(key);
    }

    // for(const QString &str : strList){
    //     qDebug() << "STRLIST: " << str;
    // }
}