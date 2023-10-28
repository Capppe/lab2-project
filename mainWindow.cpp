#include "headers/mainWindow.hpp"
#include "headers/toolBar.hpp"
#include "headers/statusBar.hpp"
#include "headers/mainMenu.hpp"

MainWindow *MainWindow::mainWindow = nullptr;

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent)
{
    qDebug() << "MainWindow!!"; 
        qDebug() << "Creating toolbar";
    this->setupToolBar();
        qDebug() << "Creating statusbar";
    this->setupStatusBar();
    this->setupMainMenu();
    this->startBackgroundProcesses();

    this->setStyleSheet(
        "QMainWindow{background-color: gray; border: none;} \
        QPushButton{background-color: black; color: white; border-radius: 5px;} \
        #mainMenuButton{ background-color: black; border-radius: 5px; } \
        #buttonLabel{ color:white; font: 22px; } \
        #buttonIcon{ color:white; font: 26px; } \
        QPushButton:hover, CustomButton:hover{border: 1px solid #f49609; color: #f49609} \
        QToolBar{background-color: black; border: none;}"
    );
    mainWindow = this;
}

void MainWindow::setupMainMenu() {
    qDebug() << "Creating mainmenu";
    MainMenu *mainMenu = new MainMenu(this);
    this->setCentralWidget(mainMenu);
    qDebug() << "Created mainmenu!";
}

void MainWindow::setupToolBar() {
    QToolBar *mainToolBar = new QToolBar;
    addToolBar(Qt::TopToolBarArea, mainToolBar);
    ToolBar *toolBar = new ToolBar(mainToolBar);
    toolBar->constructToolBar();
    toolBar->constructToolBarMenu(new QWidget(this), this->width());

    mainToolBar->addWidget(toolBar);
}

void MainWindow::setupStatusBar() {
    QToolBar *mainStatusBar = new QToolBar;
    addToolBar(Qt::BottomToolBarArea, mainStatusBar);
    StatusBar *statusBar = new StatusBar(mainStatusBar);
    statusBar->constructStatusBar();
    statusBar->bindButtons();

    mainStatusBar->addWidget(statusBar);
}

void MainWindow::startBackgroundProcesses() {
    listener = BtDeviceListener::getInstance();
    listener->moveToThread(&devListenerThread);
    devListenerThread.start();
    //QProcess::execute("bt-agent -c NoInputNoOutput");
}

void showMenu() {

}

MainWindow *MainWindow::getMainWindow(){
    return mainWindow;
}

// Adds a gradient background
void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QLinearGradient gradient(rect().topLeft(), rect().bottomLeft());
    gradient.setColorAt(0, QColor(50,50,50,255)); 
    gradient.setColorAt(0.5, QColor(100,100,100,255)); 
    gradient.setColorAt(1, QColor(50,50,50,255)); 

    // Create a QPainter to paint on the QMainWindow
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(gradient));
}
