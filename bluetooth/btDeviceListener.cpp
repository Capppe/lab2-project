#include "../headers/bt/btDeviceListener.hpp"

BtDeviceListener *BtDeviceListener::instance = nullptr;

BtDeviceListener *BtDeviceListener::getInstance(){
  if(!instance){
    instance = new BtDeviceListener();
  }
  return instance;
}

BtDeviceListener::BtDeviceListener() {
  qDebug() << "BtDeviceListener created";
    QDBusConnection::systemBus().connect(
        "org.bluez",
        "/",
        "org.freedesktop.DBus.ObjectManager",
        "InterfacesAdded",
        this,
        SLOT(deviceFound(QDBusObjectPath, QVariantMap))
    );
}

BtDeviceListener::~BtDeviceListener() {
  qDebug() << "BtDeviceListener destroyed";
}

//Methods
void BtDeviceListener::addDeviceListener(QString path){
    if(QDBusConnection::systemBus().connect(
        "org.bluez",
        path,
        "org.freedesktop.DBus.Properties",
        "PropertiesChanged",
        this,
        SLOT(propertiesChanged(QString, QVariantMap, QStringList))
    )){
        qDebug() << "Added listener on path: " << path;
    }else{
        qDebug() << "Failed to add listener on path: " << path;
    }
}

// Slots
void BtDeviceListener::deviceFound(const QDBusObjectPath &objectPath, const QVariantMap &properties){
    if(properties.contains("org.bluez.Device1")){
        qDebug() << "Device found: " << objectPath.path();
        emit(device(objectPath.path()));
    }
}

void BtDeviceListener::propertiesChanged(const QString &string, QVariantMap map, const QStringList &list){
    for(const QString &k : map.keys()){
        //qDebug() << "MAP: " << map << "\nKEY: " << k << "VALUE: " << map[k];
        if(k == "Connected"){ 
            if(map[k].toBool() == true){
                qDebug() << "Emitting: " << "deviceConnected()";
                emit(deviceConnected());
            }else{
                qDebug() << "Emitting: " << "deviceDisconnected()";
                emit(deviceDisconnected());
            }
        }
        else if(k == "Paired"){
            if(map[k].toBool() == true){
                qDebug() << "Emitting: " << "devicePaired()";
                emit(devicePaired());
            }
        }
        else if(k == "Status"){
            qDebug() << "Emitting: " << "playerStatus(" << map[k].toString() << ")";
            emit(playerStatus(map[k].toString()));
        }else if(k == "Position"){
            qDebug() << "Emitting: " << "position(" << map[k].toString() << ")";
            emit(position(map[k].toInt()));
        }else if(k == "Track"){
            qDebug() << "Emitting: " << "track(" << map[k] << ")";
            const QDBusArgument &arg = map[k].value<QDBusArgument>();
            QMap<QString, QVariant> trackMap;
            arg >> trackMap;
            emit(track(trackMap));
        }else if(k == "");
        
    }
}
