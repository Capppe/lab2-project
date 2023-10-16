#include "headers/navigationInterface.hpp"

NavigationInterface::NavigationInterface() 
{
    this->initVars();
    this->populateLayouts();
    this->populateWidgets();
    this->styleLayout();
    this->bindButtons();
}

NavigationInterface::~NavigationInterface() {} 

void NavigationInterface::initVars(){
    mainLayout = new QVBoxLayout(this);
    webView = new QWebEngineView();
}

void NavigationInterface::populateLayouts(){
    mainLayout->addWidget(webView);
}

void NavigationInterface::populateWidgets(){
    webView->setUrl(QUrl("https://maps.google.com"));
}

void NavigationInterface::styleLayout(){

}

void NavigationInterface::bindButtons(){

}

