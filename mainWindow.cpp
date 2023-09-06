#include "headers/mainWindow.hpp"

// Constructor
MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QToolBar *mainToolBar = addToolBar("");
    ToolBar *toolBar = new ToolBar(mainToolBar);
    toolBar->constructToolBarMenu(new QWidget(this), this->width());

    mainToolBar->addWidget(toolBar);

    this->setStyleSheet(
        "QMainWindow{background-color: gray; border: none;} \
        QPushButton{background-color: black; color: white; border-radius: 5px;} \
        QPushButton:hover {border: 1px solid #f49609; color: #f49609} \
        QToolBar{background-color: black; border: none;}"
    );
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
