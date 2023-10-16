#include "customButton.hpp"

CustomButton::CustomButton(const QString &text, const QString &iconPath, QWidget *parent) : QAbstractButton(parent)
{
    this->mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    this->mainLayout->setAlignment(Qt::AlignCenter);
    this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(1);

    this->setIcon(iconPath);

    this->label = new QLabel(text, this);

    this->expander = new QWidget(this);
    this->expander->setFixedHeight(30);

    this->mainLayout->addWidget(this->icon);
    this->mainLayout->addWidget(this->expander);
    this->mainLayout->addWidget(this->label);

    this->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    this->setObjectName("mainMenuButton");
    this->icon->setObjectName("buttonIcon");
    this->icon->setMaximumWidth(150);
    this->label->setMaximumWidth(150);
    this->label->setObjectName("buttonLabel");
    this->label->setAlignment(Qt::AlignCenter);

}

CustomButton::~CustomButton() {}

QString CustomButton::getText(){
    return label->text();
}

QString CustomButton::getIconText(){
    return icon->text();
}

void CustomButton::setText(const QString &text){

}

void CustomButton::setIcon(QString iconPath){
    QFileInfo file(iconPath);
    this->icon = new QLabel(this);
    this->icon->setAlignment(Qt::AlignCenter);
    if(file.isFile()){
        QPixmap pixmap(iconPath);    
        this->icon->setPixmap(pixmap.scaled(64,64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }else{
        this->icon->setText(iconPath);
    }
}

void CustomButton::mousePressEvent(QMouseEvent *event) {
    emit(this->clicked(this->getText(), this->getIconText()));
}

void CustomButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}