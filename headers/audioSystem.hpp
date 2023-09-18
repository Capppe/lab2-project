#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <QMediaPlayer>
#include <QDir>
#include <QMediaMetaData>
#include <QList>
#include <QDebug>
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

    QStandardItemModel *addToModel(QStringList fileList, QDir folder);
    QMetaObject::Connection connSongPos;
    QMetaObject::Connection connUiUpdater;
    static QMediaPlayer *player;
    static MusicInterface *musicInterface;
    static AudioSystem *instance;
};

#endif