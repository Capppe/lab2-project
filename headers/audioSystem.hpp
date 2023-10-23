#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <QRandomGenerator>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QDBusMetaType>
#include <QMediaPlayer>
#include <QMetaObject>
#include <QTreeView>
#include <QString>
#include <QFuture>
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QQueue>
#include <QList>
#include <QDir>

#include <taglib/fileref.h>
#include <taglib/tag.h>

#include "musicInterface.hpp"
#include "dbusWorker.hpp"
#include "bluetooth.hpp"

class AudioSystem 
{
public:
    // Music control
    void stop();
    void playPause();
    void skipButton();
    void rewindButton();
    void shuffleButton();
    void setPositionByUser();

    // Misc functionality
    static void constructQueue(const QModelIndex &index);
    void bindSignals();
    void updateUi();
    void browseLocalFiles();
    void parseLocalFile(const QItemSelection &selected, const QItemSelection &deselected);

    void startBtPosition();
    void stopBtPosition();
    // Getters
    static AudioSystem *getInstance();
    static MusicInterface *getMusicInterface();
    QStringList *getFilteredFilelist(QStringList filters);
    QMetaObject::Connection getConnSongPos();
    QMetaObject::Connection getConnUiUpdater();
    QMetaObject::Connection getBtSongPos();

    QList<QMetaObject::Connection> getSignalsList();

    // Setters
    void setMedia(QString path);

private:
    // Constructor & destructor
    AudioSystem();
    ~AudioSystem();

    void updatePlayPauseButton();
    void createModel();
    void checkSource();
    void updateBtUi();
    static QUrl getLocalSongUrl(const QModelIndex &index);


    QTreeView *treeView;
    QStandardItemModel *addToModel(QStringList fileList, QDir folder);
    QMetaObject::Connection connSongPos;
    QMetaObject::Connection connUiUpdater;
    QMetaObject::Connection btSongPos;
    QList<QMetaObject::Connection> signalsToDestroy;
    Bluetooth *bt;
    static QMediaPlaylist *playlist;
    static QStandardItemModel *model;
    static QMediaPlayer *player;
    static MusicInterface *musicInterface;
    static AudioSystem *instance;

    bool srcIsBt;
    QThread dbusThread;
    DBusWorker dbusWorker;
};

#endif
