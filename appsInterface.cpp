#include "headers/appsInterface.hpp"

Applications::Applications() {
    this->initVars();
    this->populateLayouts();
    this->populateWidgets();
    this->bindButtons();
    this->bindSignals();
    this->readConfig();
    this->createApps();
}

Applications::~Applications() {}

void Applications::bindButtons(){

}

void Applications::bindSignals(){

}

void Applications::initVars(){
    this->buttonLayout = new QGridLayout(this);
    this->appsList = new QList<NewApp>;
}

void Applications::populateLayouts(){
}

void Applications::populateWidgets(){

}

void Applications::styleLayout(){
    this->mainLayout->setAlignment(Qt::AlignTop);
}

//Functionality
void Applications::createAppButton(){

}

void Applications::readConfig(){
    NewApp newApp;
    QFile file(QDir::currentPath() + "/local/cfg/apps");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Errorr opening file: " << file.errorString();
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList parts = line.split('=');
        if(line.isEmpty()){
            appsList->append(newApp);
        }
        if(parts.size() == 2){
            QString key = parts[0].trimmed();
            QString value = parts[1].trimmed();
            if(key == "name"){
                newApp.name = value;
            }else if(key == "icon"){
                newApp.icon = value;
            }else if(key == "exec"){
                newApp.exec = value;
            }
        }
    }
    file.close();
}

void Applications::createApps(){
    int currRow = 0;
    int currCol = 0;
    qDebug() << "CRERATING APPS";
    for(const NewApp &app : *appsList){
        QPushButton *appButton = new QPushButton();
        appButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        // appButton->setFixedHeight(200);
        // appButton->setFixedWidth(200);
        if(app.icon.isEmpty()){
            appButton->setText(app.name);
        }else{
            QIcon icon(app.icon);
            appButton->setIcon(icon);
            appButton->setIconSize(QSize(60,60));
        }
        QObject::connect(appButton, &QPushButton::clicked, [&](){
            QProcess process;
            process.startDetached(app.exec);
        });

        if(currCol > 4){
            currCol = 0;
            ++currRow;
        }
        this->buttonLayout->addWidget(appButton, currRow, currCol);
        ++currCol;
        this->buttonLayout->setAlignment(Qt::AlignTop);
        qDebug() << "ADDED" << appButton;
    }

    if(appsList->size() < 5){
        QWidget *expander = new QWidget;
        expander->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        this->buttonLayout->addWidget(expander, 1, 1);
    }
}