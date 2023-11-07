#include "../headers/music/localAudioSystem.hpp"

LocalAudioSystem::LocalAudioSystem() 
{
    localPlayer = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
}
LocalAudioSystem::~LocalAudioSystem() {}

void LocalAudioSystem::stop(){
    localPlayer->stop();
}

void LocalAudioSystem::playPause(){
    qDebug() << "Local playPause";
    QMediaPlayer::State state = localPlayer->state();

    if(state == QMediaPlayer::PlayingState){
        localPlayer->pause();
        emit(paused());
    }else if(state == QMediaPlayer::PausedState){
        localPlayer->play();
        emit(playing());
    }
}

void LocalAudioSystem::nextButton(){

}

void LocalAudioSystem::previousButton(){

}

void LocalAudioSystem::shuffleButton(){

}

void LocalAudioSystem::setPositionByUser(){
    // qint64 pos = MusicInterface::getSliderPosition();
    // MusicInterface::updateSongPosition(pos);
    // localPlayer->setPosition(pos);
}

void LocalAudioSystem::bindSignals(){

}

void LocalAudioSystem::updateUi(){
    
}

void LocalAudioSystem::createQueue(){
    playlist->clear();
}