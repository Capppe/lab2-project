#include "headers/radioInterface.hpp"
#include "headers/audioSystem.hpp"

RadioInterface::RadioInterface()
{
    this->initVars(); 
    this->createLayout();
    this->createButtons();
    this->styleLayout();
    this->bindButtons();
}

RadioInterface::~RadioInterface() {}

void RadioInterface::initVars(){
    this->apiHandler = new APIHandler(this);
    this->mainLayout = new QVBoxLayout(this);
    this->firstWidget = new QWidget;
    this->firstLayout = new QVBoxLayout(firstWidget);
    this->buttonWidget = new QWidget;
    this->npWidget = new QWidget;
    this->stackedWidget = new QStackedWidget();

    this->buttonLayout = new QGridLayout(buttonWidget);
    this->npLayout = new QHBoxLayout(npWidget);

    this->np = new QLabel("Now playing: ");
    this->npText = new QLabel;
    this->stopButton = new QPushButton("Stop");
    this->browseButton = new QPushButton("Browse");
    this->smainWidget = new QWidget(stackedWidget);
    this->smainLayout = new QVBoxLayout(smainWidget);
    this->tmainWidget = new QWidget(stackedWidget);
    this->tmainLayout = new QVBoxLayout(tmainWidget);
}

void RadioInterface::createLayout(){
    buttonWidget->setLayout(buttonLayout);
    npWidget->setLayout(npLayout);
    smainWidget->setLayout(smainLayout);
    tmainWidget->setLayout(tmainLayout);
    
    npLayout->addWidget(np);
    npLayout->addWidget(npText);
    npLayout->addWidget(stopButton);

    firstLayout->addWidget(buttonWidget);
    firstLayout->addWidget(npWidget);
  
    firstWidget->setLayout(firstLayout);

    stackedWidget->addWidget(firstWidget);
    stackedWidget->addWidget(smainWidget);
    stackedWidget->addWidget(tmainWidget);

    mainLayout->addWidget(stackedWidget);
}

void RadioInterface::createButtons(){
    QList<QPair<QString, QString>> stations = DataStorage::readRadioStations();
    int row = 0;
    int column = 0;
    for(QPair<QString, QString> pair : stations){
        CustomButton *button = new CustomButton(pair.second, pair.first, this);
        buttonLayout->addWidget(button, row, column);
        bindSignals(button);
        setButtonStyling(button);
        column++;
        if(column >= 5){
            column = 0;
            row++;
        }
        if(row == 2 && column == 4){
            break;
        }
    }
    buttonLayout->addWidget(browseButton, 2, 4);
}

void RadioInterface::createSecondLayout(){
  this->sPicLayout = new QHBoxLayout;
  this->sinfoLayout = new QVBoxLayout;
  this->sButtonLayout = new QVBoxLayout;

  this->icon = new QLabel(this);
  this->icon->setPixmap(QPixmap(QDir::currentPath() + "/icons/radio.png").scaled(200,200,Qt::KeepAspectRatio, Qt::SmoothTransformation));
  this->name = new QLabel("Label", this);
  this->address = new QLabel("Label", this);
  this->country = new QLabel("Label", this);

  this->sstopButton = new QPushButton("Stop");
  this->seditButton = new QPushButton("Edit");

  sButtonLayout->addWidget(seditButton);
  sButtonLayout->addWidget(sstopButton);

  sinfoLayout->addWidget(name);
  sinfoLayout->addWidget(address);
  sinfoLayout->addWidget(country);

  sPicLayout->addWidget(icon);
  sPicLayout->addLayout(sinfoLayout);
  
  smainLayout->addLayout(sPicLayout);
  smainLayout->addLayout(sButtonLayout);

  stackedWidget->setCurrentIndex(1);
}

void RadioInterface::createThirdLayout(){
    this->tboxLayout = new QHBoxLayout();
    //this->tscrollArea = new QScrollArea(tmainWidget);
    this->tsearch = new QPushButton("Search");

    this->tinfo = new QLabel("Search for a station");
    this->ticon = new QLabel(this);
    this->tcountryCode = new QLabel(this);

    this->tlanguage = new QComboBox(this);
    this->tcountry = new QComboBox(this);

    tlanguage->addItem("Choose Language");
    tcountry->addItem("Choose Country");

    QObject::connect(tlanguage, QOverload<int>::of(&QComboBox::highlighted), this, &RadioInterface::langApiCall);

    QObject::connect(tcountry, QOverload<int>::of(&QComboBox::highlighted), this, &RadioInterface::countryApiCall);
    // QObject::connect(browseButton, &QPushButton::clicked, this, [&](){
    //     langApiCall();
    //     countryApiCall();
    // });

    tboxLayout->addWidget(tlanguage);
    tboxLayout->addWidget(tcountry);

    mainLayout->addWidget(tinfo);
    mainLayout->addLayout(tboxLayout);
    mainLayout->addWidget(tsearch);

    stackedWidget->setCurrentIndex(2);
}

void RadioInterface::langApiCall(){
    apiHandler->call("http://de1.api.radio-browser.info/json/languages");
    QObject::connect(apiHandler, &APIHandler::dataRecieved, this, &RadioInterface::addLangData);
    QObject::disconnect(tlanguage, QOverload<int>::of(&QComboBox::highlighted), this, &RadioInterface::langApiCall);
}

void RadioInterface::countryApiCall(){
    apiHandler->call("http://de1.api.radio-browser.info/json/countries");
    QObject::connect(apiHandler, &APIHandler::dataRecieved, this, &RadioInterface::addCountryData);
    QObject::disconnect(tcountry, QOverload<int>::of(&QComboBox::highlighted), this, &RadioInterface::countryApiCall);
}

void RadioInterface::addLangData(QStringList data){
    QRegExp regexLang("[0-9]");
    if(data.isEmpty()){
        qDebug() << "Data empty";
        return;
    }
    for(QString s : data){
        if(regexLang.indexIn(s) == -1){
            tlanguage->addItem(s);
        }
    }
}

void RadioInterface::addCountryData(QStringList data){
    if(data.isEmpty()){
        qDebug() << "Data empty";
        return;
    }
    for(QString s : data){
        tcountry->addItem(s);
    }
}

void RadioInterface::bindSignals(CustomButton *button){
    AudioSystem *as = AudioSystem::getInstance();
    QObject::connect(button, &CustomButton::clicked, this, [&](const QString &text, const QString &iconText){
        QString txt = QString(iconText); 
        as->setMedia(text);
        npText->setText(iconText);
        createSecondLayout();
        styleSecondLayout();
    });
}

void RadioInterface::bindButtons(){
    AudioSystem *as = AudioSystem::getInstance();
    QObject::connect(stopButton, &QPushButton::clicked, this, [&](){
        as->stop();
        npText->setText("");
    });

    QObject::connect(browseButton, &QPushButton::clicked, [&](){
        createThirdLayout();
        styleThirdLayout();
    });
}

void RadioInterface::styleLayout(){
    browseButton->setObjectName("browseButton");
    browseButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    buttonWidget->setObjectName("buttonWidget");
    npWidget->setObjectName("npWidget");
    npText->setObjectName("np");
    np->setObjectName("np");

    stopButton->setMinimumHeight(60);
    this->setStyleSheet("#npWidget{ background: #282828; } \
                         #np{ color: white; font-size: 16px; } \
                         #buttonLabel{ font-size: 18px; } \
                         #smainLayout{ border: 1px solid black; } \
                         #browseButton{ background-color: #282828; color: white; font-size: 18px; } \
                         #browseHeader{ font-size: 22px; color: orange; background: black; border: 1px solid black; border-radius: 10px;} \
                         QComboBox{ font-size: 22px; color: white; background: black; border: 1px solid black; border-radius: 10px;} \
                         QComboBox::drop-down{ border: none; } \
                         QComboBox:hover{ color: orange; border: 1px solid orange; } \
                         QComboBox QAbstractItemView{ background-color: gray; } \
                         ");
}

void RadioInterface::styleSecondLayout(){
  smainWidget->setStyleSheet("QWidget{ border: 1px solid black; }");
  mainLayout->setAlignment(Qt::AlignCenter);
  smainLayout->setAlignment(Qt::AlignCenter);

  seditButton->setMinimumHeight(80);
  sstopButton->setMinimumHeight(80);
}

void RadioInterface::styleThirdLayout(){
    tmainLayout->setAlignment(Qt::AlignCenter);
    tsearch->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    tlanguage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    tcountry->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    //tinfo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    tinfo->setAlignment(Qt::AlignCenter);
    tinfo->setObjectName("browseHeader");
}

void RadioInterface::setButtonStyling(CustomButton *button){
    button->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}
