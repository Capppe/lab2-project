#ifndef LOCALAUDIOSYSTEM_HPP
#define LOCALAUDIOSYSTEM_HPP

#include <QMediaPlaylist>
#include <QMediaPlayer>

#include "abstractAudioSystem.hpp"

class LocalAudioSystem : public AbstractAudioSystem
{
    Q_OBJECT

public:
    LocalAudioSystem();
    ~LocalAudioSystem();

    // Media control
    void stop() override;
    void playPause() override;
    void nextButton() override;
    void previousButton() override;
    void shuffleButton() override;
    void setPositionByUser() override;

    // Functionality
    void bindSignals() override;
    void updateUi() override;
    void createQueue();


private:
    QMediaPlayer *localPlayer;
    QMediaPlaylist *playlist;
};

#endif