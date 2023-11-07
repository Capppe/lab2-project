#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QToolBar>
#include <QMainWindow>
#include <QtWidgets>
#include <QThread>

#include "bt/btDeviceListener.hpp"
#include "bt/btConnectedDevices.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Constructor
    MainWindow(QWidget *parent = nullptr);

    static MainWindow *getMainWindow();
    void setupMainMenu();

private:
    void setupToolBar();
    void setupStatusBar();
    void startBackgroundProcesses();

    static MainWindow *mainWindow;
    QWidget *mainWidget;

    BtDeviceListener *listener;
    QThread devListenerThread;
    QThread btAgentThread;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif
