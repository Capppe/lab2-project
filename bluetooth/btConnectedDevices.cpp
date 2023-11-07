#include "../headers/bt/btConnectedDevices.hpp"

BtConnectedDevices::BtConnectedDevices() {}
BtConnectedDevices::~BtConnectedDevices() {}

void BtConnectedDevices::executeMethod(QVariant arg){
}

QStringList BtConnectedDevices::getConnectedDevices(){
    QMap<QString, QMap<QString, QMap<QString, QVariant>>> devices = discDevs.getDiscoveredDevices(1);
    QMap<QString, QMap<QString, QVariant>> secondMap;
    QMap<QString, QVariant> thirdMap;
    QStringList connectedDevices;
    
    for(const auto &key : devices.keys()){
        secondMap = devices.value(key);
        
        if(!key.contains("/org/bluez/hci0/dev_")){
            continue;
        }
        
        for(const auto &key2 : secondMap.keys()){
            thirdMap = secondMap.value(key2);

            for(const auto &key3 : thirdMap.keys()){
                if(key2 == "org.bluez.Device1"){
                    if(thirdMap[key3] == "Connected" && thirdMap[key3].toBool() == true){
                        connectedDevices.append(key);
                    }
                }else if(key2 == "org.bluez.MediaControl1"){
                    const QDBusObjectPath &path = thirdMap[key3].value<QDBusObjectPath>();
                    connectedDevices.append(path.path());
                }
            }
        }
    }
    return connectedDevices;
}

void BtConnectedDevices::addListeners(){
    QStringList devices = getConnectedDevices();
    BtDeviceListener *listener = BtDeviceListener::getInstance();

    qDebug() << "SIZE: " << devices.size();

    for(const QString &device : devices){
        listener->addDeviceListener(device);
    }
}