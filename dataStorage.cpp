#include "headers/dataStorage.hpp"
#include "headers/utils.hpp"

DataStorage::DataStorage() {}
DataStorage::~DataStorage() {}

QList<QPair<QString, QString>> DataStorage::readBtDevices(){
    QFile file(QDir::currentPath() + "/local/bluetooth/pairedDevices.json");
    QList<QPair<QString, QString>> devicesList;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        QString jsonData = in.readAll();
        file.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData.toUtf8());
        if(jsonDocument.isArray()){
            QJsonArray deviceArray = jsonDocument.array();
            for(const auto &deviceValue : deviceArray){
                if(deviceValue.isObject()){
                    QJsonObject deviceObject = deviceValue.toObject();
                    //QPair<QString, QString> devices(deviceObject["DeviceName"].toString(), deviceObject["DeviceAddress"].toString());
                    QPair<QString, QString> devices;
                    devices.first = deviceObject["DeviceName"].toString();
                    devices.second = deviceObject["DeviceAddress"].toString();
                    devicesList.append(devices);
                }
            }
        }
    }else{
        qDebug() << "Cant open file for reading!";
    }
    return devicesList;
}

void DataStorage::saveBtDevice(const QString &name, const QString &address){
    QList<QPair<QString, QString>> knownDevices = readBtDevices();
    QJsonArray deviceArray;

    if(!knownDevices.contains(QPair(name, address))){
        qDebug() << "Not contain!";
        knownDevices.append(QPair(name, address));
    }

    deviceArray = createDeviceArray(knownDevices);

    writeToBtFile(deviceArray);
}

void DataStorage::removeBtDevice(const QString &address){
    QList<QPair<QString, QString>> knownDevices = readBtDevices();

    knownDevices.erase(std::remove_if(knownDevices.begin(), knownDevices.end(),
        [address](const QPair<QString, QString> &pair) {
            return pair.second == address;
        }),
    knownDevices.end());

    QJsonArray deviceArray = createDeviceArray(knownDevices);
    writeToBtFile(deviceArray);
}

void DataStorage::saveRadioStations(const QString &name, const QString &address){
    QString line = name + "," + address;
    writeToFile("/local/radio/stations", line);
}

QList<QPair<QString, QString>> DataStorage::readRadioStations(){
    return Utils::parseFileContent(readFromFile("/local/radio/stations"));
}

void DataStorage::writeToFile(QString path, QString line){
    QFile file(QDir::currentPath() + path);
    QList<QString> currentContents = readFromFile(path);

    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
        QTextStream out(&file);
        out << line;
        file.close();
    }else{
        qDebug() << "Could not open file: " << path;
    }
}

QList<QString> DataStorage::readFromFile(QString path){
    QList<QString> content;
    QFile file(QDir::currentPath() + path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine();
            content.append(line);
        }
        file.close();
    }

    return content;
}

void DataStorage::writeToBtFile(QJsonArray array){
    QJsonDocument doc(array);
    QFile file(QDir::currentPath() + "/local/bluetooth/pairedDevices.json");
    
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
        QTextStream out(&file);
        out << doc.toJson();
        file.close();
    }else{
        qDebug() << "Cant open file for writing!";
    }
}

QJsonArray DataStorage::createDeviceArray(QList<QPair<QString, QString>> knownDevices){
    QJsonObject deviceObject;
    QJsonArray deviceArray;
    for(QPair<QString, QString> device: knownDevices){
        deviceObject["DeviceName"] = device.first;
        deviceObject["DeviceAddress"] = device.second;
        deviceArray.append(deviceObject);
    }

    return deviceArray;
}
