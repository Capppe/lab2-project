#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <iostream>
#include <string>
#include <QToolBar>
#include <QMainWindow>
#include <QtWidgets>
#include "../ui_test.h"
#include "toolBar.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Constructor
    MainWindow(QWidget *parent = nullptr);

private:
//Member functions
    
//Member variables 
    Ui::MainWindow ui;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif