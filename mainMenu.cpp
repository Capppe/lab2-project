#include "headers/mainMenu.hpp"
#include "headers/buttonHandler.hpp"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MainMenu::bindButtons() {
    ButtonHandler *buttonHandler = ButtonHandler::getInstance();
    if(buttonHandler){
        connect(ui.musicButton, &QPushButton::clicked, buttonHandler, &ButtonHandler::musicButton);
    }
}