#ifndef CUSTOMBUTTON_HPP
#define CUSTOMBUTTON_HPP

#include <QAbstractButton>
#include <QStyleOption>
#include <QBoxLayout>
#include <QFileInfo>
#include <QPainter>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <QIcon>

class CustomButton : public QAbstractButton
{
    Q_OBJECT

public:
    CustomButton(const QString &text, const QString &iconPath, QWidget *parent);
    ~CustomButton();

    QString getText();
    QString getIconText();

    void setText(const QString &text);
    void setIcon(QString iconPath);
    void setExpansion();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QBoxLayout *mainLayout;
    QWidget *expander;
    QLabel *icon;
    QLabel *label;

signals:
    void clicked(const QString &text, const QString &iconText);
};

#endif