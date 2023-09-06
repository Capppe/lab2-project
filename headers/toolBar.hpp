#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP

#include <iostream>
#include <string>
#include <QToolBar>
#include <QtWidgets>
#include <QPushButton>
#include "../ui_drawerMenu.h"

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    //Constructor
    ToolBar(QToolBar *toolBar);

    void constructToolBarMenu(QWidget *toolBarMenu, int width);

    //Setters
    void setNavMenuTxt(std::string txt);

    QPushButton *toolBarMenuButton;


private:
    // Toolbar constructors
    void constructToolBar();
    void createToolBarIcons();

    QToolBar *toolBar;
    QLabel *navMenu;
    QWidget *toolBarMenu;

public slots:
    void toolBarButtonPressed();

};

#endif