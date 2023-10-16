#include "headers/buttonHandler.hpp"
#include "headers/toolBar.hpp"
#include <QCoreApplication>
#include "headers/mainWindow.hpp"
#include "headers/musicInterface.hpp"
#include "headers/mainMenu.hpp"
#include "headers/audioSystem.hpp"
#include "headers/bluetoothInterface.hpp"
#include "headers/appsInterface.hpp"
#include "headers/navigationInterface.hpp"
#include "headers/radioInterface.hpp"
#include "headers/APIhandler.hpp"

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
        ToolBar::setNavMenuTxt("Music");
    }
}

void ButtonHandler::bluetoothButton() {
    MainWindow *mainWindow = MainWindow::getMainWindow();
    BluetoothInterface *btInterface = new BluetoothInterface();
    if(mainWindow) {
        mainWindow->setCentralWidget(btInterface);
        ToolBar::setNavMenuTxt("Bluetooth");
    }
}

void ButtonHandler::navigationButton() {
    MainWindow *mainWindow = MainWindow::getMainWindow();
    NavigationInterface *navIface = new NavigationInterface();
    if(mainWindow) {
        mainWindow->setCentralWidget(navIface);
        ToolBar::setNavMenuTxt("Navigation");
    }
}

void ButtonHandler::radioButton() {
    MainWindow *mainWindow = MainWindow::getMainWindow();
    RadioInterface *radioIface = new RadioInterface();
    if(mainWindow) {
        mainWindow->setCentralWidget(radioIface);
        ToolBar::setNavMenuTxt("Radio");
    }
}

void ButtonHandler::applicationsButton() {
    MainWindow *mainWindow = MainWindow::getMainWindow();
    Applications *apps = new Applications();
    if(mainWindow) {
        mainWindow->setCentralWidget(apps);
        ToolBar::setNavMenuTxt("Applications");

    }
}

// Toolbar
void ButtonHandler::homeButton() {
    qDebug() << "Home button";
    MainWindow *mainWindow = MainWindow::getMainWindow();
    if(mainWindow) {
        mainWindow->setupMainMenu();
        ToolBar::setNavMenuTxt("Home");
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
    AudioSystem::getInstance()->shuffleButton();
}
