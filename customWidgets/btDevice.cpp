#include "btDevice.hpp"

BtDevice::BtDevice() {}

BtDevice::BtDevice(const QString name, const QString address, QWidget *parent = nullptr) : QWidget(parent)
{
    qDebug() << "Creating custom btDevice!";
    mainLayout = new QVBoxLayout(this);
    
    this->visibleLayout = new QHBoxLayout;
    this->name = new QLabel(name);
    this->address = new QLabel(address);
    this->deviceIconPixmap = getDeviceIcon(1);
    this->deleteIconPixmap = QPixmap(QDir::currentPath() + "/icons/close_icon_X.png");
    this->deviceIcon = new QLabel;
    this->statusLabel = new QLabel;
    this->expanderWidget = new QWidget;
    this->devInfoWidget = new QWidget;
    this->devInfoLayout = new QVBoxLayout(this->devInfoWidget);
    this->deleteButton = new QPushButton;

    this->hiddenLayoutContainer = new QWidget;
    this->hiddenLayout = new QHBoxLayout(hiddenLayoutContainer);
    this->connectButton = new QPushButton("Connect");
    this->autoConnCheck = new QCheckBox("Auto-connect");

    setStyling();
    bindButtons();
    bindSignals();
    addLayouts();
}

BtDevice::~BtDevice()
{
}

QPixmap BtDevice::getDeviceIcon(int device){
    switch (device){
        case 1:
            return QPixmap(QDir::currentPath() + "/icons/bt_phone.png");
            break;
        
        default:
            return QPixmap(QDir::currentPath() + "/icons/bt_phone.png");
            break;
    }
}

void BtDevice::bindButtons(){
    QObject::connect(connectButton, &QPushButton::clicked, this, &BtDevice::onConnectButtonClicked);
    QObject::connect(deleteButton, &QPushButton::clicked, this, &BtDevice::onRemoveButtonClicked);
}

void BtDevice::bindSignals(){
    BtDeviceListener *listener = BtDeviceListener::getInstance();
    QObject::connect(listener, &BtDeviceListener::deviceConnected, this, &BtDevice::setOnConnected);
    QObject::connect(listener, &BtDeviceListener::deviceDisconnected, this, &BtDevice::setOnDisconnected);
}

void BtDevice::onConnectButtonClicked(){
    qDebug() << "Emitting connectButtonClicked(" << this->address->text() << ")";
    emit(connectButtonClicked(this->address->text()));
}

void BtDevice::onDisconnectButtonClicked(){
    qDebug() << "Emitting disconnectButtonClicked(" << this->address->text() << ")";
    emit(disconnectButtonClicked(this->address->text()));
}

void BtDevice::onRemoveButtonClicked(){
    this->autoConnCheck->setVisible(false);
    emit(removeButtonClicked(this->address->text()));
}

void BtDevice::setStyling(){
    deleteButton->setIcon(QIcon(deleteIconPixmap));
    deleteButton->setIconSize(QSize(45,45));
    deleteButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    deleteButton->setMaximumWidth(100);
    deleteButton->setObjectName("deleteButton");
    deviceIcon->setPixmap(deviceIconPixmap.scaled(70,120, Qt::KeepAspectRatio));

    expanderWidget->setObjectName("expander");
    expanderWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    hiddenLayoutContainer->setVisible(false);
    hiddenLayoutContainer->setMinimumHeight(80);

    connectButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    autoConnCheck->setVisible(false);

    this->setMaximumHeight(100);
    setStyleSheet("BtDevice{ background-color: black; border-radius: 20px; } \
                  BtDevice:hover{ border: 1px solid #f49609 } \
                  QLabel{ font: 20px; } \
                  QCheckBox{ background: black; font: 18px; color: white; } \
                  QCheckBox:hover{ color: #f49609; } \
                  QCheckBox::indicator{ border: 1px solid white; height: 20px; width: 20px; border-radius: 10px; } \
                  QCheckBox::indicator:checked{ background-color: green; } \
                  QCheckBox:checked{ color: green; } \
                  #connected{ background-color: black; border: 1px solid green; } \
                  #deleteButton:hover{ border: 1px solid #e03614; }"
                );
}

void BtDevice::addLayouts(){
    visibleLayout->addWidget(deviceIcon);
    devInfoLayout->addWidget(name);
    devInfoLayout->addWidget(address);
    devInfoWidget->setLayout(devInfoLayout);
    
    visibleLayout->addWidget(devInfoWidget);
    visibleLayout->addWidget(expanderWidget);
    visibleLayout->addWidget(statusLabel);
    visibleLayout->addWidget(expanderWidget);
    visibleLayout->addWidget(deleteButton);

    hiddenLayout->addWidget(connectButton);
    hiddenLayout->addWidget(autoConnCheck);
    hiddenLayoutContainer->setLayout(hiddenLayout);

    mainLayout->addLayout(visibleLayout);
    mainLayout->addWidget(hiddenLayoutContainer);
}

QString BtDevice::getAddress() const {
    return this->address->text();
}

QString BtDevice::getName() const {
    return this->name->text();
}

void BtDevice::setOnPaired(){
    this->autoConnCheck->setVisible(true);
}

void BtDevice::setOnConnecting(){
    this->statusLabel->setText("Connecting...");
}

void BtDevice::setOnDisconnecting(){
    this->statusLabel->setText("Disconnecting...");
}

void BtDevice::setOnConnected(){
    qDebug() << "Setting on connect";
    QObject::disconnect(connectButton, &QPushButton::clicked, this, &BtDevice::onConnectButtonClicked);
    QObject::disconnect(connectButton, &QPushButton::clicked, this, &BtDevice::onDisconnectButtonClicked);
    connectButton->setText("Disconnect");
    this->statusLabel->setText("");
    QObject::connect(connectButton, &QPushButton::clicked, this, &BtDevice::onDisconnectButtonClicked, Qt::UniqueConnection);
}

void BtDevice::setOnDisconnected(){
    qDebug() << "Setting on disconnect";
    QObject::disconnect(connectButton, &QPushButton::clicked, this, &BtDevice::onConnectButtonClicked);
    QObject::disconnect(connectButton, &QPushButton::clicked, this, &BtDevice::onDisconnectButtonClicked);
    this->statusLabel->setText("");
    connectButton->setText("Connect");
    QObject::connect(connectButton, &QPushButton::clicked, this, &BtDevice::onConnectButtonClicked, Qt::UniqueConnection);
}

//Event overrides
void BtDevice::mousePressEvent(QMouseEvent *event) {
    hiddenLayoutContainer->setVisible(!hiddenLayoutContainer->isVisible());
    this->setMaximumHeight(hiddenLayoutContainer->isVisible() ? 200 : 100);
}

void BtDevice::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
