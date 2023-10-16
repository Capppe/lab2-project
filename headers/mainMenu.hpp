#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <QWidget>
#include <QDir>

#include "../uic/ui_test.h"
#include "../customWidgets/customButton.hpp"

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    MainMenu(QWidget *parent = nullptr);

private:
    Ui::MainWindow ui;
    void bindButtons();
    void createButtons();

    CustomButton *musicButton;
    CustomButton *btButton;
    CustomButton *navButton;
    CustomButton *radioButton;

    CustomButton *appsButton;
};

#endif