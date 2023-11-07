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
                if(!key2.contains("org.bluez.Device")){
                    continue;
                }
                if(key3 == "Alias"){
                    //qDebug() << thirdMap[key3].toString();
                }
                if(key3 == "Connected"){
                    if(thirdMap[key3].toBool() == true){
                        connectedDevices.append(key2);
                    }
                }
            }
        }
    }
    qDebug() << connectedDevices;
    return connectedDevices;
}