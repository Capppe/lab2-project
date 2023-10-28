#include "../headers/bluetooth.hpp"
#include "../headers/bluetoothInterface.hpp"
#include "../headers/dataStorage.hpp"

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

    QObject::connect(localDevice, &QBluetoothLocalDevice::hostModeStateChanged, [&](QBluetoothLocalDevice::HostMode state) {
        qDebug() << "State: " << state;
    });

    localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
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