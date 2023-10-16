#ifndef APPSINTERFACE_HPP
#define APPSINTERFACE_HPP

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTextStream>
#include <QPushButton>
#include <QProcess>
#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QDir>

class Applications : public QWidget
{
public:
    Applications();
    ~Applications();

    void bindButtons();
    void bindSignals();
    void initVars();
    void populateLayouts();
    void populateWidgets();
    void styleLayout();

    void createAppButton();
    void readConfig();
    void createApps();

private:
    QVBoxLayout *mainLayout;
    QGridLayout *buttonLayout;

    struct NewApp {
        QString name;
        QString icon;
        QString exec;
    };
    QList<NewApp> *appsList;
};

#endif