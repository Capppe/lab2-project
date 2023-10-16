#include "settingsRow.hpp"

SettingsRow::SettingsRow(const QString &title, const QString &desc, QWidget *parent = nullptr) : QWidget(parent) 
{
    qDebug() << "Creating a settings row";
    this->mainLayout = new QVBoxLayout(this);

    this->visibleLayout = new QHBoxLayout;
    this->verticalLayout = new QVBoxLayout;

    this->title = new QLabel(title);
    this->description = new QLabel(desc);
    this->expanderWidget = new QWidget;

    this->active = new QCheckBox();

    this->bindButtons();
    this->addLayouts();
    this->setStyling();
}

//Header constructor
SettingsRow::SettingsRow(const QString &title, QWidget *parent) {
    this->mainLayout = new QVBoxLayout(this);

    this->visibleLayout = new QHBoxLayout;

    this->title = new QLabel(title);

    this->addHeaderLayouts();
    this->setHeaderStyling();
}

SettingsRow::~SettingsRow() {}

void SettingsRow::bindButtons(){
    QObject::connect(this->active, &QCheckBox::stateChanged, [&](const int &state){
        emit(this->newState(state));
    });
}

void SettingsRow::addLayouts(){
    verticalLayout->addWidget(this->title);
    verticalLayout->addWidget(this->description);

    visibleLayout->addLayout(verticalLayout);
    visibleLayout->addWidget(this->expanderWidget);
    visibleLayout->addWidget(this->active);

    mainLayout->addLayout(visibleLayout);
}

void SettingsRow::addHeaderLayouts(){
    visibleLayout->addWidget(this->title);
    mainLayout->addLayout(visibleLayout);
}

void SettingsRow::setStyling(){
    this->setMinimumHeight(40);

    this->title->setObjectName("title");
    this->description->setObjectName("desc");

    expanderWidget->setObjectName("expander");
    expanderWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    this->setStyleSheet("SettingsRow{ background-color: black; border-radius: 10px; } \
                        SettingsRow:hover{ border: 1px solid #f49609 } \
                        QCheckBox::indicator{ background-color: black; border: 1px solid white; width: 24px; height: 24px; } \
                        QCheckBox::indicator:checked{ background-color: #f49609; } \
                        QCheckBox:checked{  } \
                        QLabel{ font: 20px; } \
                        #desc{ font: 14px; } \
                        #title{ text-decoration: underline; color: #f49609; } \
    ");
}

void SettingsRow::setHeaderStyling(){
    this->setStyleSheet("SettingsRow{ background: black; border-bottom: 5px solid #f49609; border-radius: 0px; } \
                        QLabel{ font: 26px; }\
    ");
}

void SettingsRow::mousePressEvent(QMouseEvent *event) {
    //hiddenLayoutContainer->setVisible(!hiddenLayoutContainer->isVisible());
    //this->setMaximumHeight(hiddenLayoutContainer->isVisible() ? 200 : 100);
    this->active->setChecked(!this->active->isChecked());
}

void SettingsRow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}