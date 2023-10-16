#ifndef SETTINGSROW_HPP
#define SETTINGSROW_HPP

#include <QStyleOption>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPainter>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QLabel>


class SettingsRow : public QWidget
{
    Q_OBJECT
public:
    SettingsRow(const QString &title, QWidget *parent); // Header
    SettingsRow(const QString &title, const QString &desc, QWidget *parent); // Bool settings
    //SettingsRow(const QString &title, const QString &desc, QWidget *parent); 
    ~SettingsRow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void setStyling();
    void addLayouts();
    void bindButtons();

    void setHeaderStyling();
    void addHeaderLayouts();

    QVBoxLayout *mainLayout;
    QHBoxLayout *visibleLayout;
    QVBoxLayout *verticalLayout;

    QWidget *containerWidget;
    QWidget *expanderWidget;

    QLabel *title;
    QLabel *description;

    QCheckBox *active;

    bool isHeader;

signals:
    void newState(int state);
    void autoConnAddressUpdate(const QString &address);
};

#endif