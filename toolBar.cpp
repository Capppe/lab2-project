#include "headers/toolBar.hpp"

QLabel *ToolBar::navMenu = nullptr;

ToolBar::ToolBar(QToolBar *toolBar) {
    this->toolBar = toolBar;
}

void ToolBar::constructToolBar() {
    toolBar->setFixedHeight(26);
    toolBar->setMovable(false);
    this->createToolBarIcons();
}

void ToolBar::constructToolBarMenu(QWidget *tbMenu, int width) {
    toolBarMenu = tbMenu;

    Ui_DrawerWidget drawerWidget;
    drawerWidget.setupUi(toolBarMenu);

    toolBarMenu->show();
    toolBarMenu->setVisible(false);
    toolBarMenu->move(0,26);
    toolBarMenu->setMinimumWidth(width);

    connect(drawerWidget.drawer_bt_button, &QPushButton::clicked, this, &ToolBar::btButtonPressed);

    drawerWidget.drawer_bt_button->setIcon(QIcon(QDir::currentPath() + "/icons/bt.png"));
    drawerWidget.drawer_bt_button->setIconSize(QSize(30,30));
    drawerWidget.drawer_bt_button->setText("");
    drawerWidget.drawer_wifi_button->setIcon(QIcon(QDir::currentPath() + "/icons/wifi.png"));
    drawerWidget.drawer_wifi_button->setIconSize(QSize(30,30));
    drawerWidget.drawer_wifi_button->setText("");
    drawerWidget.drawer_settings_button->setIcon(QIcon(QDir::currentPath() + "/icons/settings.png"));
    drawerWidget.drawer_settings_button->setIconSize(QSize(30,30));
    drawerWidget.drawer_settings_button->setText("");

    drawerWidget.drawer_volSliderMin_label->setPixmap(QPixmap(QDir::currentPath() + "/icons/volumeDown.png").scaled(30,30, Qt::KeepAspectRatio));
    drawerWidget.drawer_volSliderMax_label->setPixmap(QPixmap(QDir::currentPath() + "/icons/volumeUp.png").scaled(30,30, Qt::KeepAspectRatio));

    drawerWidget.drawer_brightSliderMin_label->setPixmap(QPixmap(QDir::currentPath() + "/icons/brightness_lower.png").scaled(30,30, Qt::KeepAspectRatio));
    drawerWidget.drawer_brightSliderMax_label->setPixmap(QPixmap(QDir::currentPath() + "/icons/brightness.png").scaled(30,30, Qt::KeepAspectRatio));
}

void ToolBar::createToolBarIcons() {
    navMenu = new QLabel("Home");
    navMenu->setStyleSheet("color: #f49609; font-weight: bold; font-size: 16px;");
    toolBar->addWidget(navMenu);
    
    //spacer to keep navMenu to the left
    QWidget *spacerWidget = new QWidget();
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    toolBar->addWidget(spacerWidget);

    QLabel *btStatus = new QLabel(toolBar);
    btStatus->setPixmap(QPixmap(QDir::currentPath() + "/icons/24x24/bt_24x24.png"));
    
    QLabel *internetStatus = new QLabel(toolBar);
    internetStatus->setPixmap(QPixmap(QDir::currentPath() + "/icons/24x24/wifi_inactive_24x24.png"));

    QLabel *clock = new QLabel("22:49");
    clock->setStyleSheet("color: white; font-size: 20px;");

    toolBarMenuButton = new QPushButton(toolBar);
    toolBarMenuButton->setIcon(QIcon(QDir::currentPath() + "/icons/24x24/drawer_24x24.png"));
    connect(toolBarMenuButton, &QPushButton::clicked, this, &ToolBar::toolBarButtonPressed);

    
    toolBar->addWidget(btStatus);
    toolBar->addWidget(internetStatus);
    toolBar->addWidget(clock);
    toolBar->addWidget(toolBarMenuButton);
    toolBar->setStyleSheet("padding-left: 2px;");
}

void ToolBar::toolBarButtonPressed() {
    toolBarMenu->setVisible(!toolBarMenu->isVisible());
    toolBarMenu->raise();
}

void ToolBar::btButtonPressed() {

}

void ToolBar::wifiButtonPressed() {

}

void ToolBar::settingsButtonPressed() {

}
//Setters
void ToolBar::setNavMenuTxt(std::string txt){
    navMenu->setText(QString::fromStdString(txt));
}