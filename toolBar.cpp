#include "headers/toolBar.hpp"

ToolBar::ToolBar(QToolBar *toolBar) {
    this->toolBar = toolBar;
    this->constructToolBar();
    this->createToolBarIcons();
    connect(toolBarMenuButton, &QPushButton::clicked, this, &ToolBar::toolBarButtonPressed);
}

void ToolBar::constructToolBar() {
    toolBar->setFixedHeight(26);
    toolBar->setMovable(false);
}

void ToolBar::constructToolBarMenu(QWidget *tbMenu, int width) {
    toolBarMenu = tbMenu;

    Ui_DrawerWidget drawerWidget;
    drawerWidget.setupUi(toolBarMenu);

    toolBarMenu->show();
    toolBarMenu->setVisible(true);
    toolBarMenu->move(0,26);
    toolBarMenu->setMinimumWidth(width);
}

void ToolBar::createToolBarIcons() {
    navMenu = new QLabel("Home");
    navMenu->setStyleSheet("color: #f49609; font-weight: bold;");
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
    
    toolBar->addWidget(btStatus);
    toolBar->addWidget(internetStatus);
    toolBar->addWidget(clock);
    toolBar->addWidget(toolBarMenuButton);
    toolBar->setStyleSheet("padding-left: 2px;");
}

void ToolBar::toolBarButtonPressed() {
    toolBarMenu->setVisible(!toolBarMenu->isVisible());
}

//Setters
void ToolBar::setNavMenuTxt(std::string txt){
    this->navMenu->setText(QString::fromStdString(txt));
}