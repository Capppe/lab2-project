#include "headers/audioSystem.hpp"
#include "headers/utils.hpp"

AudioSystem *AudioSystem::instance = nullptr;
MusicInterface *AudioSystem::musicInterface = nullptr;
QMediaPlayer *AudioSystem::player = nullptr;

AudioSystem::AudioSystem() 
{
    qDebug() << "AudioSys created!";
    player = new QMediaPlayer;
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
    connSongPos = QObject::connect(player, &QMediaPlayer::mediaStatusChanged, [&]() {
        updateUi();
        player->play();
    });
    connUiUpdater = QObject::connect(player, &QMediaPlayer::positionChanged, [&](qint64 pos) {
        MusicInterface::updateSongPosition(pos);
    });
}

// Ui updates
void AudioSystem::updateUi() {
    qDebug() << "Update called";
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
    }else {
        qDebug() << "Do something?";
    }
    updatePlayPauseButton();
}

void AudioSystem::skipButton(){
    
}

void AudioSystem::rewindButton(){
    int currPos = player->position() * 1000;
    if(currPos/5 > 5){
        player->setPosition(0);
    }else {
        qDebug() << "No";
    }
}

void AudioSystem::browseLocalFiles() {
    //musicInterface->toggleView();
    QTreeView *treeView = musicInterface->getTreeView();
    QDir folder(QDir::currentPath() + "/local/audioFiles");
    QStringList filters;
    filters << "*.mp3";
    QStringList fileList = folder.entryList(filters, QDir::Files);
    QStandardItemModel *model = addToModel(fileList, folder);

    model->setColumnCount(4);
    model->setHorizontalHeaderLabels({"Track", "Artist", "Album", "Length"});

    treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
    treeView->header()->setFont(QFont("Roboto Mono", 24));
    treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    treeView->setModel(model);

    musicInterface->setTreeView(treeView);
    musicInterface->setItemPressed();
    musicInterface->toggleView();
    
    //QString url = QDir::currentPath() + path;
    //player->setMedia(QUrl::fromLocalFile(url));
    //player->setVolume(30); //testing only
    //player->play();
}

void AudioSystem::parseLocalFile(const QItemSelection &selected, const QItemSelection &deselected){
    Q_UNUSED(deselected)

    qDebug() << "Parsing";

    QString selection = selected.indexes().at(0).data().toString();
    QDir folder(QDir::currentPath() + "/local/audioFiles");
    QStringList filters(selection);
    QStringList fileList = folder.entryList(filters, QDir::Files);
    QString fileName = folder.filePath(fileList[0]);
    setMedia(fileName);
    qDebug() << "FileName: " << fileName;
}

QStandardItemModel *AudioSystem::addToModel(QStringList fileList, QDir folder){
    QStandardItemModel *model = new QStandardItemModel;
    QMediaPlayer *mediaPlayer = new QMediaPlayer;
        qDebug() << "Filelist: " << fileList;
    for (int i = 0; i < fileList.size(); ++i) {
        QString fileName = folder.filePath(fileList[i]);
        mediaPlayer->setMedia(QUrl::fromLocalFile(fileName));
        //TODO add mediaplayer connection (onStateChanged...)? 
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(fileList[i])
                 << new QStandardItem(mediaPlayer->metaData(QMediaMetaData::ContributingArtist).toString())
                 << new QStandardItem(mediaPlayer->metaData(QMediaMetaData::AlbumTitle).toString())
                 << new QStandardItem(QString::number(mediaPlayer->duration() / 1000) + "s");

        for (QStandardItem *item : rowItems){
            item->setFont(QFont("Roboto Mono", 16));
            item->setSizeHint(QSize(120,70));
            item->setEditable(false);
        }
        model->appendRow(rowItems);
    }
    return model;
}

void AudioSystem::setPositionByUser() {
    qint64 pos = MusicInterface::getSliderPosition();
    MusicInterface::updateSongPosition(pos);
    player->setPosition(pos);
}

// Setters
void AudioSystem::setMedia(QString path){
    qDebug() << "Playing? Path= " << path;
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