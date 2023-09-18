#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <QWidget>
#include "../uic/ui_test.h"

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    MainMenu(QWidget *parent = nullptr);

    void bindButtons();

private:
    Ui::MainWindow ui;
};

#endif