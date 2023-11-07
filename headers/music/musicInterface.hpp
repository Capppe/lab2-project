#ifndef MUSICINTERFACE_HPP
#define MUSICINTERFACE_HPP

#include <QtWidgets>

#include "../bt/btDeviceListener.hpp"
#include "../bt/music/status.hpp"
#include "../bt/btConnectedDevices.hpp"
#include "../bt/music/btAudioSystem.hpp"
#include "abstractAudioSystem.hpp"
#include "localAudioSystem.hpp"

class MusicInterface : public QWidget
{
    Q_OBJECT
public:
    // Constructor & destructor
    MusicInterface();
    ~MusicInterface();

    // Setters
    static void setSongName(QString name);
    static void setArtist(QString artist);
    static void setAlbum(QString album);
    static void setAlbumImage(std::string path);
    static void setSongLength(QString length);
    static void setSongSliderDuration(qint64 dur);
    static void setPlayPauseButtonIcon(int i);
    void setModel(QStandardItemModel *model);
    void setTreeView(QTreeView *treeView);
    void setItemPressed();

    // Misc functionality
    static int getSliderPosition();
    void toggleView();
    QTreeView *browseLocalFiles();
    QTreeView *getTreeView();
    void bindButtons();

public slots:
    static void updateSongPosition(qint64 pos);

private:

    // Setup
    void initVars();
    void populateWidgets();
    void styleLayout();
    void populateLayouts();
    void bindSignals();
    void getSource();
    void getCurrent();
    void updateUi(QMap<QString, QVariant> map = QMap<QString, QVariant>());

    QWidget *containerWidget;
    QWidget *fileWidget;
    QWidget *albumWidget;
    QTableWidget *tableWidget;
    QStackedWidget *stackedWidget;
    
    QVBoxLayout *containerLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *albumLayout;
    QHBoxLayout *fileLayout;
    QVBoxLayout *musicInfoLayout;
    QHBoxLayout *musicLengthLayout;
    QVBoxLayout *musicControlLayout;
    QHBoxLayout *musicButtonLayout;

    static QLabel *albumImage;
    static QLabel *songLength;
    static QLabel *songCurrent;
    static QLabel *songName;
    static QLabel *songArtist;
    static QLabel *songAlbum;
    static QSlider *songLengthSlider;

    static QPushButton *playPauseSong;
    QPushButton *localFiles;
    QPushButton *prevSong;
    QPushButton *nextSong;
    QPushButton *shuffleSong;

    QStandardItemModel *model;
    QTreeView *treeView;
    QScrollerProperties scrollerProperties;

    BtConnectedDevices connDevs;
    AbstractAudioSystem *audioSystem;

signals:
    void playPauseClicked();
    void nextClicked();
    void prevClicked();
};

#endif