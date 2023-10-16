#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP

#include <QToolBar>
#include <QtWidgets>
#include <QPushButton>
#include "../uic/ui_drawerMenu.h"

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    //Constructor
    ToolBar(QToolBar *toolBar);

    // Setup
    void constructToolBarMenu(QWidget *toolBarMenu, int width);
    void constructToolBar();

    //Setters
    static void setNavMenuTxt(std::string txt);

    QPushButton *toolBarMenuButton;

private:
    // Toolbar constructors
    void createToolBarIcons();

    QToolBar *toolBar;
    static QLabel *navMenu;
    QWidget *toolBarMenu;

public slots:
    void toolBarButtonPressed();
    void btButtonPressed();
    void wifiButtonPressed();
    void settingsButtonPressed();

};

#endif