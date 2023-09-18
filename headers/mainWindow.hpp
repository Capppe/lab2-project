#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QToolBar>
#include <QMainWindow>
#include <QtWidgets>

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

    static MainWindow *mainWindow;
    QWidget *mainWidget;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif