#include "headers/musicInterface.hpp"
#include "headers/buttonHandler.hpp"
#include "headers/audioSystem.hpp"
#include "headers/utils.hpp"

QLabel *MusicInterface::songName = nullptr;
QLabel *MusicInterface::songArtist = nullptr;
QLabel *MusicInterface::songAlbum = nullptr;
QLabel *MusicInterface::songLength = nullptr;
QLabel *MusicInterface::songCurrent = nullptr;
QLabel *MusicInterface::albumImage = nullptr;
QSlider *MusicInterface::songLengthSlider = nullptr;
QPushButton *MusicInterface::playPauseSong = nullptr;

MusicInterface::MusicInterface()
{
    this->initVars();
    this->populateLayouts();
    this->populateWidgets();
    this->styleLayout();
    this->bindButtons();
    qDebug() << "Music created";
}

MusicInterface::~MusicInterface() 
{
    QObject::disconnect(AudioSystem::getInstance()->getConnSongPos());
    QObject::disconnect(AudioSystem::getInstance()->getConnUiUpdater());
    qDebug() << "Music destroyed";
}

void MusicInterface::bindButtons() {
    ButtonHandler *buttonHandler = ButtonHandler::getInstance();

    QObject::connect(this->playPauseSong, &QPushButton::clicked, buttonHandler, &ButtonHandler::playPauseSong);
    QObject::connect(this->localFiles, &QPushButton::clicked, buttonHandler, &ButtonHandler::browseLocalFiles);
    QObject::connect(this->songLengthSlider, &QSlider::sliderReleased, buttonHandler, &ButtonHandler::sliderChanged);
    QObject::connect(this->nextSong, &QPushButton::clicked, buttonHandler, &ButtonHandler::skip);
    QObject::connect(this->prevSong, &QPushButton::clicked, buttonHandler, &ButtonHandler::rewind);
    QObject::connect(this->shuffleSong, &QPushButton::clicked, buttonHandler, &ButtonHandler::shuffle);
}
// Ui
void MusicInterface::initVars() {
    mainLayout = new QVBoxLayout(this);
    containerLayout = new QVBoxLayout;
    containerWidget = new QWidget;
    fileWidget = new QWidget;
    albumWidget = new QWidget;
    albumLayout = new QHBoxLayout(albumWidget);
    fileLayout = new QHBoxLayout(fileWidget);
    musicInfoLayout = new QVBoxLayout;
    musicLengthLayout = new QHBoxLayout;
    musicControlLayout = new QVBoxLayout;
    musicButtonLayout = new QHBoxLayout;

    stackedWidget = new QStackedWidget(containerWidget);

    albumImage = new QLabel;
    songLength = new QLabel;
    songCurrent = new QLabel;
    songName = new QLabel;
    songArtist = new QLabel;
    songAlbum = new QLabel;
    songLengthSlider = new QSlider;
    localFiles = new QPushButton;
    prevSong = new QPushButton;
    nextSong = new QPushButton;
    playPauseSong = new QPushButton;
    shuffleSong = new QPushButton;

    treeView = new QTreeView;
    model = new QStandardItemModel;
}

void MusicInterface::populateLayouts() {
    QWidgetList musicInfoWidgets = {songName, songArtist, songAlbum, songLengthSlider};
    QWidgetList musicWidgets = {localFiles, prevSong, playPauseSong, nextSong, shuffleSong};
    QWidget *expander = new QWidget;
    expander->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    for (QWidget *widget : musicInfoWidgets){
        musicInfoLayout->addWidget(widget);
    }

    for (QWidget *widget : musicWidgets){
        musicButtonLayout->addWidget(widget);
        widget->setMinimumSize(40,60);
    }
    albumLayout->addWidget(albumImage);
    musicLengthLayout->addWidget(songCurrent);
    musicLengthLayout->addWidget(expander);
    musicLengthLayout->addWidget(songLength);

    fileWidget->setLayout(fileLayout);
    albumWidget->setLayout(albumLayout);

    stackedWidget->addWidget(albumWidget);
    stackedWidget->addWidget(fileWidget);
    stackedWidget->setCurrentIndex(0);

    musicInfoLayout->addLayout(musicLengthLayout);
    fileLayout->addWidget(treeView);
    albumLayout->addLayout(musicInfoLayout);
    containerLayout->addWidget(stackedWidget);
    musicControlLayout->addLayout(musicButtonLayout);
    containerLayout->addLayout(musicControlLayout);
    containerWidget->setLayout(containerLayout);
    mainLayout->addWidget(containerWidget);
}

void MusicInterface::populateWidgets() {
    songName->setText("No song currently playing!");
    songArtist->setText("artist");
    songAlbum->setText("album");
    songCurrent->setText("00:00");
    songLength->setText("00:00");

    localFiles->setIcon(QIcon(QDir::currentPath() + "/icons/files.png"));
    prevSong->setIcon(QIcon(QDir::currentPath() + "/icons/backward.png"));
    nextSong->setIcon(QIcon(QDir::currentPath() + "/icons/forward.png"));
    playPauseSong->setIcon(QIcon(QDir::currentPath() + "/icons/playbutton.png"));
    shuffleSong->setIcon(QIcon(QDir::currentPath() + "/icons/shuffle.png"));

    localFiles->setIconSize(QSize(30,30));
    prevSong->setIconSize(QSize(30,30));
    nextSong->setIconSize(QSize(30,30));
    playPauseSong->setIconSize(QSize(30,30));
    shuffleSong->setIconSize(QSize(30,30));

    scrollerProperties = QScroller::scroller(treeView->viewport())->scrollerProperties();
    QVariant OvershootPolicy = QVariant::fromValue<QScrollerProperties::OvershootPolicy>(QScrollerProperties::OvershootAlwaysOff);
    scrollerProperties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, OvershootPolicy);
    scrollerProperties.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, OvershootPolicy);
}

void MusicInterface::styleLayout() {
    containerWidget->setObjectName("containerWidget");
    songName->setObjectName("songName");
    songArtist->setObjectName("artist");
    songAlbum->setObjectName("songAlbum");
    songCurrent->setObjectName("songCurrent");
    songLength->setObjectName("songLength");

    this->setStyleSheet(
        "#containerWidget{ background-color: black; border: 1px solid white; border-radius: 19px; } \
        #songName{ font-size: 20px; } \
        #artist, #songAlbum, #songCurrent, #songLength{ font-size: 16px; } \
        QPushButton{  } \
        QLabel{ color: white; } \
        QSlider{ height: 20px; padding-left: 5px; padding-right: 5px; } \
        QSlider::groove:horizontal{ height: 2px; border: 1px solid black; } \
        QSlider::handle:horizontal{ background: #f49609; width: 14px; border-radius: 7px; margin: -6px; } \
        QSlider::sub-page:horizontal{ background: #f49609; } \
        QHeaderView::section { background-color: rgb(50,50,50); color: #f49609; font-size: 20px; } \
        QTreeView{ background: black; selection-background-color: transparent; } \
        QTreeView::selected{ background: black; } \
        QTreeView::item{ background: black; color: white; height: 70px; } \
        QTreeView::item:selected:first{ border-left: 1px solid #f49609; border-top: 1px solid #f49609; border-bottom: 1px solid #f49609; background: black; color: #f49609; height: 70px; } \
        QTreeView::item:selected{ border-top: 1px solid #f49609; border-bottom: 1px solid #f49609; background: black; color: #f49609; height: 70px; } \
        QTreeView::item:selected:last{ border-right: 1px solid #f49609; border-top: 1px solid #f49609; border-bottom: 1px solid #f49609; background: black; color: #f49609; height: 70px; } \
        QSlider::add-page:horizontal{ background: white; }"
    );

    songLengthSlider->setOrientation(Qt::Horizontal);QWidget *expander = new QWidget;
    expander->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    albumImage->setPixmap(QPixmap(QDir::currentPath() + "/icons/cd.png").scaled(250,250,Qt::KeepAspectRatioByExpanding));

    treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    treeView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    treeView->setRootIsDecorated(false);
}

void MusicInterface::toggleView(){
    stackedWidget->setCurrentIndex(stackedWidget->currentIndex() == 0 ? 1 : 0);
}

// Getters
int MusicInterface::getSliderPosition(){
    return songLengthSlider->value();
}

QTreeView *MusicInterface::getTreeView(){
    return treeView;
}

// Setters
void MusicInterface::updateSongPosition(qint64 pos){
    songLengthSlider->setValue(pos);
    songCurrent->setText(Utils::getTimeFormat(pos));
}

void MusicInterface::setModel(QStandardItemModel *model){
    this->model = model;
}

void MusicInterface::setTreeView(QTreeView *treeView){
    this->treeView = treeView;
}

void MusicInterface::setSongName(QString name){
    songName->setText(name);
}

void MusicInterface::setArtist(QString artist){
    songArtist->setText(artist);
}

void MusicInterface::setAlbum(QString album){
    songAlbum->setText(album);
}

void MusicInterface::setAlbumImage(std::string path){
    albumImage->setPixmap(QPixmap(QString::fromStdString(path)));
}

void MusicInterface::setSongLength(QString seconds){
    songLength->setText(seconds);
}

void MusicInterface::setSongSliderDuration(qint64 dur){
    songLengthSlider->setMaximum(dur);
}

void MusicInterface::setItemPressed(){
    QObject::connect(treeView, &QTreeView::clicked, this, [&](const QModelIndex &index){
        AudioSystem::constructQueue(index);
    });
}

void MusicInterface::setPlayPauseButtonIcon(int i){
    if(i == 0){ playPauseSong->setIcon(QIcon(QDir::currentPath() + "/icons/pausebutton.png"));}
    else{ playPauseSong->setIcon(QIcon(QDir::currentPath() + "/icons/playbutton.png"));}
}