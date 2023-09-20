#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QMediaMetaData>
#include <QList>
#include <QDebug>
#include <QQueue>
#include "musicInterface.hpp"

class AudioSystem 
{
public:
    // Music control
    void playPause();
    void skipButton();
    void rewindButton();
    void setPositionByUser();

    // Misc functionality
    static void constructQueue(const QModelIndex &index);
    void bindSignals();
    void updateUi();
    void browseLocalFiles();
    void parseLocalFile(const QItemSelection &selected, const QItemSelection &deselected);

    // Getters
    static AudioSystem *getInstance();
    static MusicInterface *getMusicInterface();
    QStringList *getFilteredFilelist(QStringList filters);
    QMetaObject::Connection getConnSongPos();
    QMetaObject::Connection getConnUiUpdater();

    // Setters
    static void setMedia(QString path);

private:
    // Constructor & destructor
    AudioSystem();
    ~AudioSystem();

    void updatePlayPauseButton();
    static QUrl getLocalSongUrl(const QModelIndex &index);

    static QMediaPlaylist *playlist;

    QStandardItemModel *addToModel(QStringList fileList, QDir folder);
    QMetaObject::Connection connSongPos;
    QMetaObject::Connection connUiUpdater;
    static QStandardItemModel *model;
    static QMediaPlayer *player;
    static MusicInterface *musicInterface;
    static AudioSystem *instance;
};

#endif