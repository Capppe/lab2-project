#include "headers/mainMenu.hpp"
#include "headers/buttonHandler.hpp"
#include "headers/bt/btConnectedDevices.hpp"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    this->createButtons();
    this->bindButtons();
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MainMenu::bindButtons(){
    ButtonHandler *buttonHandler = ButtonHandler::getInstance();
    if(buttonHandler){
        connect(musicButton, &CustomButton::clicked, buttonHandler, &ButtonHandler::musicButton);
        connect(btButton, &CustomButton::clicked, buttonHandler, &ButtonHandler::bluetoothButton);
        connect(navButton, &CustomButton::clicked, buttonHandler, &ButtonHandler::navigationButton);
        //connect(radioButton, &CustomButton::clicked, buttonHandler, &ButtonHandler::radioButton);
        connect(appsButton, &CustomButton::clicked, buttonHandler, &ButtonHandler::applicationsButton);
        connect(radioButton, &CustomButton::clicked, [&](){
            BtConnectedDevices discDevs;
            qDebug() << "Executing discDevs";
            discDevs.getConnectedDevices();
        });
    }
}

void MainMenu::createButtons(){
    musicButton = new CustomButton("Music", QDir::currentPath() + "/icons/64x64/music.png", this);
    btButton = new CustomButton("Bluetooth", QDir::currentPath() + "/icons/bt.png", this);
    navButton = new CustomButton("Navigation", QDir::currentPath() + "/icons/nav.png", this);
    radioButton = new CustomButton("Radio", QDir::currentPath() + "/icons/radio.png", this);
    appsButton = new CustomButton("Applications", QDir::currentPath() + "/icons/appDrawer.png", this);

    ui.gridLayout->addWidget(musicButton, 0, 0);
    ui.gridLayout->addWidget(btButton, 0, 1);
    ui.gridLayout->addWidget(navButton, 0, 2);
    ui.gridLayout->addWidget(radioButton, 0, 3);
    ui.gridLayout->addWidget(appsButton, 1, 4);
}
