#ifndef BTAUDIOSYSTEM_HPP
#define BTAUDIOSYSTEM_HPP

#include <QObject>

#include "mediaControl.hpp"
#include "../../music/musicInterface.hpp"
#include "../../music/abstractAudioSystem.hpp"

class BtAudioSystem : public AbstractAudioSystem
{
    Q_OBJECT

public:
    BtAudioSystem();
    ~BtAudioSystem();

    void stop() override;
    void playPause() override;
    void nextButton() override;
    void previousButton() override;
    void shuffleButton() override;
    void setPositionByUser() override;

    // Functionality
    void bindSignals() override;
    void updateUi() override;

private:
    //MediaPlayer mPlayer;
};

#endif