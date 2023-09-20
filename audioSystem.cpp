#include "headers/audioSystem.hpp"
#include "headers/utils.hpp"

AudioSystem *AudioSystem::instance = nullptr;
MusicInterface *AudioSystem::musicInterface = nullptr;
QMediaPlayer *AudioSystem::player = nullptr;
QMediaPlaylist *AudioSystem::playlist = nullptr;
QStandardItemModel *AudioSystem::model = nullptr;

AudioSystem::AudioSystem() 
{
    qDebug() << "AudioSys created!";
    player = new QMediaPlayer;
    playlist = new QMediaPlaylist;

    player->setVolume(10); //DEBUGGING TO NOT GET BLASTED
}
AudioSystem::~AudioSystem() 
{
    qDebug() << "AudioSys destroyed!";
}

void AudioSystem::bindSignals() {
    if(!player){
        player = new QMediaPlayer;
    }
    connSongPos = QObject::connect(player, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        updateUi();
        if(status == QMediaPlayer::EndOfMedia){
            qDebug() << "End of media!";
            playlist->next();
            player->play();
        }
    });
    connUiUpdater = QObject::connect(player, &QMediaPlayer::positionChanged, [&](qint64 pos) {
        MusicInterface::updateSongPosition(pos);
    });
}

// Ui updates
void AudioSystem::updateUi() {
    if(player->state() == QMediaPlayer::PlayingState || player->state() == QMediaPlayer::PausedState){
        QVariant songName = player->metaData(QMediaMetaData::Title);
        QVariant artistName = player->metaData(QMediaMetaData::AlbumArtist);
        QVariant albumName = player->metaData(QMediaMetaData::AlbumTitle);

        MusicInterface::setSongName(songName.isValid() ? songName.toString() : "Title unknown");
        MusicInterface::setArtist(artistName.isValid() ? artistName.toString() : "Artist unknown");
        MusicInterface::setAlbum(albumName.isValid() ? albumName.toString() : "Album unknown");

        MusicInterface::setSongLength(Utils::getTimeFormat(player->duration()));
        MusicInterface::setSongSliderDuration(player->duration());
        MusicInterface::updateSongPosition(player->position());
        updatePlayPauseButton();
    }
}

void AudioSystem::updatePlayPauseButton() {
    MusicInterface::setPlayPauseButtonIcon(player->state() == QMediaPlayer::PausedState ? 1 : 0);
}

// Button logic
void AudioSystem::playPause(){
    if(player->state() == QMediaPlayer::PlayingState){
        player->pause();
    }else if(player->state() == QMediaPlayer::PausedState){
        player->play();
    }else{
        qDebug() << "Do something";
    }
    updatePlayPauseButton();
}

void AudioSystem::skipButton(){
    playlist->next();
    player->play();
}

void AudioSystem::rewindButton(){
    if(player->position() > 4000){
        player->setPosition(0);
    }else {
        playlist->previous();
        player->play();
    }
}

// Local music playing fuctionality
void AudioSystem::constructQueue(const QModelIndex &index){
    for (int row = index.row(); row < model->rowCount(); ++row) {
        QModelIndex nextSongIndex = index.siblingAtColumn(0).siblingAtRow(row);
        playlist->addMedia((getLocalSongUrl(nextSongIndex)));
        qDebug() << "Enqueued song: " << index.siblingAtColumn(0).siblingAtRow(row).data(Qt::DisplayRole).toString();
    }
    playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    player->setPlaylist(playlist);
    player->play();
}

QUrl AudioSystem::getLocalSongUrl(const QModelIndex &index){
    QString songName;
    if(index.column() > 0){
        songName = index.siblingAtColumn(0).data(Qt::DisplayRole).toString();
    }else{
        songName = index.data(Qt::DisplayRole).toString();
    }

    QUrl songUrl = QUrl::fromLocalFile(QDir::currentPath() + "/local/audioFiles/" + songName);

    if(!songUrl.isValid()){
        return QUrl();
    }
    return songUrl;
}

void AudioSystem::browseLocalFiles() {
    QTreeView *treeView = musicInterface->getTreeView();
    QDir folder(QDir::currentPath() + "/local/audioFiles");
    QStringList filters;
    filters << "*.mp3";
    QStringList fileList = folder.entryList(filters, QDir::Files);
    model = addToModel(fileList, folder);

    model->setColumnCount(4);
    model->setHorizontalHeaderLabels({"Track", "Artist", "Album", "Length"});

    treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
    treeView->header()->setFont(QFont("Roboto Mono", 24));
    treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    treeView->setModel(model);

    musicInterface->setTreeView(treeView);
    musicInterface->setItemPressed();
    musicInterface->toggleView();
}


void AudioSystem::parseLocalFile(const QItemSelection &selected, const QItemSelection &deselected){
    Q_UNUSED(deselected)

    QString selection = selected.indexes().at(0).data().toString();
    QDir folder(QDir::currentPath() + "/local/audioFiles");
    QStringList filters(selection);
    QStringList fileList = folder.entryList(filters, QDir::Files);
    QString fileName = folder.filePath(fileList[0]);
    setMedia(fileName);
}


QStandardItemModel *AudioSystem::addToModel(QStringList fileList, QDir folder){
    QStandardItemModel *model = new QStandardItemModel;
    QMediaPlayer *mediaPlayer = new QMediaPlayer;
    for (int i = 0; i < fileList.size(); ++i) {
        QString fileName = folder.filePath(fileList[i]);
        mediaPlayer->setMedia(QUrl::fromLocalFile(fileName));
        //TODO add mediaplayer connection (onStateChanged...)? 
        QList<QStandardItem*> rowItems;
        QStandardItem *songName = new QStandardItem(fileList[i]);
        QStandardItem *artistName = new QStandardItem(mediaPlayer->metaData(QMediaMetaData::ContributingArtist).toString());
        QStandardItem *albumName = new QStandardItem(mediaPlayer->metaData(QMediaMetaData::AlbumTitle).toString());
        QStandardItem *songLength = new QStandardItem(QString::number(mediaPlayer->duration() / 1000) + "s");

        songName->setData(fileList[i], Qt::DisplayRole);
        artistName->setData(mediaPlayer->metaData(QMediaMetaData::ContributingArtist).toString(), Qt::DisplayRole);
        albumName->setData(mediaPlayer->metaData(QMediaMetaData::AlbumTitle).toString(), Qt::DisplayRole);
        songLength->setData(QString::number(mediaPlayer->duration() / 1000) + "s", Qt::DisplayRole);


        rowItems << songName << artistName << albumName << songLength;

        for (QStandardItem *item : rowItems){
            item->setFont(QFont("Roboto Mono", 16));
            item->setSizeHint(QSize(120,70));
            item->setEditable(false);
        }
        model->appendRow(rowItems);
    }
    return model;
}


// Setters
void AudioSystem::setPositionByUser() {
    qint64 pos = MusicInterface::getSliderPosition();
    MusicInterface::updateSongPosition(pos);
    player->setPosition(pos);
}

void AudioSystem::setMedia(QString path){
    qDebug() << "Playing? Path= " << path;
    player->stop();
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
}

// Getters
QMetaObject::Connection AudioSystem::getConnSongPos() {
    return connSongPos;
}

QMetaObject::Connection AudioSystem::getConnUiUpdater() {
    return connUiUpdater;
}

AudioSystem *AudioSystem::getInstance() {
    if(!instance){
        instance = new AudioSystem;
    }
    return instance;
}

MusicInterface *AudioSystem::getMusicInterface() {
    musicInterface = new MusicInterface;
    return musicInterface;
}