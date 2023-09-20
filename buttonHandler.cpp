#include "headers/buttonHandler.hpp"
#include <QCoreApplication>
#include "headers/mainWindow.hpp"
#include "headers/musicInterface.hpp"
#include "headers/mainMenu.hpp"
#include "headers/audioSystem.hpp"

ButtonHandler *ButtonHandler::instance = nullptr;

ButtonHandler::ButtonHandler(QObject *parent) : QObject(parent)
{
    qDebug() << "Buttonhandler created";
}

ButtonHandler::~ButtonHandler() 
{
    qDebug() << "Buttonhandler destroyed";
}

ButtonHandler *ButtonHandler::getInstance() {
    if(!instance){
        instance = new ButtonHandler();
    }
    return instance;
}

// Main menu
void ButtonHandler::musicButton() {
    MainWindow *mainWindow = MainWindow::getMainWindow();
    if(mainWindow) {
        AudioSystem *as = AudioSystem::getInstance();
        mainWindow->setCentralWidget(AudioSystem::getMusicInterface());
        as->updateUi();
        as->bindSignals();
    }
}

// Toolbar
void ButtonHandler::homeButton() {
    qDebug() << "Home button";
    MainWindow *mainWindow = MainWindow::getMainWindow();
    if(mainWindow) {
        mainWindow->setupMainMenu();
    }
}

void ButtonHandler::backButton() {

}

void ButtonHandler::volButton() {

}

void ButtonHandler::volDownButton() {

}

void ButtonHandler::volUpButton() {

}

void ButtonHandler::powerButton() {

}

void ButtonHandler::settingsButton() {

}

// MusicInterface
void ButtonHandler::playPauseSong() {
    AudioSystem *audioSystem = AudioSystem::getInstance();
    audioSystem->playPause();
}

void ButtonHandler::browseLocalFiles() {
    AudioSystem *audioSystem = AudioSystem::getInstance();
    audioSystem->browseLocalFiles();
}

void ButtonHandler::sliderChanged() {
    AudioSystem *audioSystem = AudioSystem::getInstance();
    audioSystem->setPositionByUser();
}

void ButtonHandler::rewind() {
    AudioSystem::getInstance()->rewindButton();
}

void ButtonHandler::skip() {
    AudioSystem::getInstance()->skipButton();
}

void ButtonHandler::shuffle() {
    
}