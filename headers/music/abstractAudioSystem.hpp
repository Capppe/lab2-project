#ifndef ABSTRACTAUDIOSYSTEM_HPP
#define ABSTRACTAUDIOSYSTEM_HPP

#include <QObject>

class AbstractAudioSystem : public QObject
{
    Q_OBJECT

public:
    // Media Control
    virtual void stop() = 0;
    virtual void playPause() = 0;
    virtual void nextButton() = 0;
    virtual void previousButton() = 0;
    virtual void shuffleButton() = 0;
    virtual void setPositionByUser() = 0;

    // Functionality
    virtual void bindSignals() = 0;
    virtual void updateUi() = 0;

signals:
    void playing();
    void paused();
    void skip();
    void previous();
};

#endif