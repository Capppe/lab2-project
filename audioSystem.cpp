#include "headers/music/audioSystem.hpp"
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
    musicInterface = getMusicInterface();
    srcIsBt = false;
    createModel();
    //checkSource();

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
    
    signalsToDestroy.append(QObject::connect(player, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        updateUi();
        if(status == QMediaPlayer::EndOfMedia){
            playlist->next();
            player->play();
        }
    }));
    
    signalsToDestroy.append(QObject::connect(player, &QMediaPlayer::positionChanged, [&](qint64 pos) {
        MusicInterface::updateSongPosition(pos);
    }));
}

// Ui updates
void AudioSystem::updateUi() {
    if(srcIsBt){
        return;
    }
    if(player->state() == QMediaPlayer::PlayingState || player->state() == QMediaPlayer::PausedState){
        QVariant songName = player->metaData(QMediaMetaData::Title);
        QVariant artistName = player->metaData(QMediaMetaData::AlbumArtist);
        QVariant albumName = player->metaData(QMediaMetaData::AlbumTitle);
        QFileInfo fileInfo(player->currentMedia().request().url().toString());
         
        MusicInterface::setSongName(songName.isValid() ? songName.toString() : fileInfo.completeBaseName());
        MusicInterface::setArtist(artistName.isValid() ? artistName.toString() : "Artist unknown");
        MusicInterface::setAlbum(albumName.isValid() ? albumName.toString() : "Album unknown");

        MusicInterface::setSongLength(Utils::getTimeFormat(player->duration()));
        MusicInterface::setSongSliderDuration(player->duration());
        MusicInterface::updateSongPosition(player->position());
        updatePlayPauseButton();
    }
}

void AudioSystem::updatePlayPauseButton() {
    if(srcIsBt){
        // MusicInterface::setPlayPauseButtonIcon(bt->getBtMusicStatus() == "playing" ? 1 : 0);
    }else{
        MusicInterface::setPlayPauseButtonIcon(player->state() == QMediaPlayer::PausedState ? 1 : 0);
    }
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

void AudioSystem::shuffleButton(){
    int random = QRandomGenerator::global()->bounded(0, model->rowCount());
    constructQueue(model->index(random, 0));
    playlist->setPlaybackMode(QMediaPlaylist::Random);
}

// Local music playing fuctionality
void AudioSystem::constructQueue(const QModelIndex &index){
    playlist->clear();
    int currentRow = index.row();
    int rowCount = model->rowCount();
    for (; currentRow < rowCount + index.row(); ++currentRow) {
        int wrappedRow = currentRow % rowCount;
        QModelIndex nextSongIndex = index.siblingAtColumn(0).siblingAtRow(wrappedRow);
        playlist->addMedia((getLocalSongUrl(nextSongIndex)));
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

void AudioSystem::createModel(){
    QDir folder(QDir::currentPath() + "/local/audioFiles");
    QStringList filters;
    filters << "*.mp3";
    QStringList fileList = folder.entryList(filters, QDir::Files);
    model = addToModel(fileList, folder);
    model->setColumnCount(4);
    model->setHorizontalHeaderLabels({"Track", "Artist", "Album", "Length"});
}

void AudioSystem::browseLocalFiles() {
    treeView = musicInterface->getTreeView();
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
    for (int i = 0; i < fileList.size(); ++i) {
        QString fileName = folder.filePath(fileList[i]);
        QString title;
        QString artist;
        QString album;
        QString duration;

        TagLib::FileRef file(fileName.toUtf8().constData());
        if(!file.isNull() && file.tag()) {
            TagLib::Tag *tag = file.tag();
            title = tag->title().toCString(true);
            artist = tag->artist().toCString(true);
            album = tag->album().toCString(true);
        }
        if(!file.isNull() && file.audioProperties()){
            TagLib::AudioProperties *audioProperties = file.audioProperties();
            duration = Utils::getTimeFormat(audioProperties->lengthInMilliseconds());
        }

        QList<QStandardItem*> rowItems;
        QStandardItem *songName = new QStandardItem(fileList[i]);
        QStandardItem *artistName = new QStandardItem(artist == "" ? "-" : artist);
        QStandardItem *albumName = new QStandardItem(album == "" ? "-" : album);
        QStandardItem *songLength = new QStandardItem(duration == "" ? "-" : duration);

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

void AudioSystem::setMedia(QString path){
    qDebug() << path;
    qDebug() << "Playing? Path= " << path;
    QUrl url(path);

    player->stop();
    if(url.isLocalFile()){
        player->setMedia(QUrl::fromLocalFile(path));
    }else{
        player->setMedia(QMediaContent(path));
    }
    player->play();
    qDebug() << "Done";
}

// Getters
QList<QMetaObject::Connection> AudioSystem::getSignalsList() {
    return signalsToDestroy;
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
