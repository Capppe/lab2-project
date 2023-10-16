#include "headers/statusBar.hpp"
#include "headers/buttonHandler.hpp"
#include "headers/mainWindow.hpp"

StatusBar::StatusBar(QToolBar *statusBar)
{
    this->statusBar = statusBar;
}

void StatusBar::constructStatusBar(){
    statusBar->setMinimumHeight(64);
    statusBar->setMovable(false);
    this->createButtons();
    this->getCurrentVolume();
}

void StatusBar::createButtons(){
    barLayout = new QHBoxLayout(this);
    buttonWidget = new QWidget;
    buttonLayout = new QHBoxLayout(buttonWidget);
    homeButton = new QPushButton;
    volButton = new QPushButton;
    volUpButton = new QPushButton;
    volDownButton = new QPushButton;
    powerButton = new QPushButton;
    settingsButton = new QPushButton;
    volControlWidget = new QWidget;
    volControlLayout = new QHBoxLayout(volControlWidget);
    volSlider = new QSlider;
    spacerWidget = new QWidget;

    homeButton->setIcon(QIcon(QDir::currentPath() + "/icons/home.png"));
    volButton->setIcon(QIcon(QDir::currentPath() + "/icons/volumeUp.png"));
    volUpButton->setIcon(QIcon(QDir::currentPath() + "/icons/volumeUp.png"));
    volDownButton->setIcon(QIcon(QDir::currentPath() + "/icons/volumeDown.png"));
    powerButton->setIcon(QIcon(QDir::currentPath() + "/icons/shutdown.png"));
    settingsButton->setIcon(QIcon(QDir::currentPath() + "/icons/settings.png"));
    
    homeButton->setIconSize(QSize(40,40));
    volButton->setIconSize(QSize(40,40));
    volDownButton->setIconSize(QSize(20,20));
    volUpButton->setIconSize(QSize(20,20));
    powerButton->setIconSize(QSize(40,40));
    settingsButton->setIconSize(QSize(40,40));
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    statusBar->setStyleSheet("QPushButton:hover { border: 1px solid #f49609;}");
    volUpButton->setStyleSheet("QPushButton:hover { border: 1px solid #f49609;}");
    volDownButton->setStyleSheet("QPushButton:hover { border: 1px solid #f49609;}");
    volControlWidget->setStyleSheet("QWidget{background-color: #282828; border-radius: 20px;}");
    volSlider->setOrientation(Qt::Horizontal);
    
    homeButton->setMinimumSize(QSize(58,58));
    volButton->setMinimumSize(QSize(58,58));
    powerButton->setMinimumSize(QSize(58,58));
    settingsButton->setMinimumSize(QSize(58,58));
    volUpButton->setMinimumSize(QSize(40,40));
    volDownButton->setMinimumSize(QSize(40,40));

    volControlLayout->addWidget(volButton);
    volControlLayout->addWidget(volDownButton);
    volControlLayout->addWidget(volSlider);
    volControlLayout->addWidget(volUpButton);
    volControlWidget->setLayout(volControlLayout);

    buttonLayout->addWidget(powerButton);
    buttonLayout->addWidget(settingsButton);
    buttonWidget->setLayout(buttonLayout);

    volControlWidget->setMinimumWidth(350);
    barLayout->setSpacing(30);
    buttonLayout->setSpacing(60);

    volSlider->setValue(this->getCurrentVolume());

    QWidgetList widgetList = {homeButton, volControlWidget, spacerWidget, buttonWidget};
    for(QWidget *widget : widgetList){
        barLayout->addWidget(widget);
    }
}

void StatusBar::bindButtons() {
    ButtonHandler *buttonHandler = ButtonHandler::getInstance();
    connect(homeButton, &QPushButton::clicked, buttonHandler, &ButtonHandler::homeButton);
    connect(volUpButton, &QPushButton::clicked, this, &StatusBar::onVolumeUpClicked);
    connect(volDownButton, &QPushButton::clicked, this, &StatusBar::onVolumeDownClicked);
}

void StatusBar::onVolumeUpClicked(){
    int currentVolume = volSlider->value();
    if(currentVolume < 100 && currentVolume + 10 <= 100){
        volSlider->setValue(currentVolume + 10);
        QProcess::execute("pactl set-sink-volume @DEFAULT_SINK@ +10%");
    }else{
        volSlider->setValue(100);
        QProcess::execute("pactl set-sink-volume @DEFAULT_SINK@ 100%");
    }
}

void StatusBar::onVolumeDownClicked(){
    int currentVolume = volSlider->value();
    if(currentVolume > 0){
        volSlider->setValue(currentVolume - 10);
        QProcess::execute("pactl set-sink-volume @DEFAULT_SINK@ -10%");
    }
}

int StatusBar::getCurrentVolume(){
    QProcess *process = new QProcess();
    process->start("sh", QStringList() << "-c" << "pactl get-sink-volume @DEFAULT_SINK@ | awk '{print $5}'");
    process->waitForFinished();
    QString output = process->readAllStandardOutput();
    qDebug() << "Output: "<<output.trimmed().toInt();
    return output.trimmed().remove("%").toInt();
}