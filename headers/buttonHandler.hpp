#ifndef BUTTONHANDLER_HPP
#define BUTTONHANDLER_HPP

#include <QObject>

class ButtonHandler : public QObject
{
    Q_OBJECT
public:
    static ButtonHandler *getInstance();

public slots:
    // Main menu
    void musicButton();
    void bluetoothButton();
    void navigationButton();
    void radioButton();
    void applicationsButton();

    // ToolBar
    void homeButton();
    void backButton();
    void volButton();
    void volDownButton();
    void volUpButton();
    void powerButton();
    void settingsButton();

    // MusicInterface
    void playPauseSong();
    void browseLocalFiles();
    void sliderChanged();
    void rewind();
    void skip();
    void shuffle();

private:
    // Constructor & destructor
    ButtonHandler(QObject *parent = nullptr);
    ~ButtonHandler();

    static ButtonHandler *instance;
};

#endif
