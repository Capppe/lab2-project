#ifndef DATASTORAGE_HPP
#define DATASTORAGE_HPP

#include <QJsonDocument>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QIODevice>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QPair>
#include <QDir>

class DataStorage
{
public:
    DataStorage();
    ~DataStorage();

    static void saveBtDevice(const QString &name, const QString &address);
    static void removeBtDevice(const QString &address);
    static QList<QPair<QString, QString>> readBtDevices();

    static void saveRadioStations(const QString &name, const QString &address);
    static QList<QPair<QString, QString>> readRadioStations();
private:
    static void writeToBtFile(QJsonArray array);
    static void writeToFile(QString path, QString line);
    static QList<QString> readFromFile(QString path);
    static QJsonArray createDeviceArray(QList<QPair<QString, QString>> knownDevices);
};

#endif
