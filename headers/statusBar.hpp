#ifndef STATUSBAR_HPP
#define STATUSBAR_HPP

#include <QToolBar>
#include <QDebug>
#include "../uic/ui_statusBar.h"

class StatusBar : public QWidget
{
    Q_OBJECT

public:
    StatusBar(QToolBar *statusBar);

    void constructStatusBar();
    void bindButtons();

private:
    QToolBar *statusBar;
    QHBoxLayout *barLayout;
    QHBoxLayout *buttonLayout;
    QWidget *buttonWidget;
    QPushButton *homeButton;
    QPushButton *volButton;
    QPushButton *volUpButton;
    QPushButton *volDownButton;
    QPushButton *powerButton;
    QPushButton *settingsButton;
    QWidget *volControlWidget;
    QHBoxLayout *volControlLayout;
    QSlider *volSlider;
    QWidget *spacerWidget;

    void createButtons();
};

#endif