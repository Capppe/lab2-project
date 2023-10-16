#ifndef NAVIGATIONINTERFACE_HPP
#define NAVIGATIONINTERFACE_HPP

#include <QWebEngineView>
#include <QVBoxLayout>
#include <QWidget>

#include "navigationSystem.hpp"

class NavigationInterface : public QWidget
{
    Q_OBJECT

public:
    NavigationInterface();
    ~NavigationInterface();

private:
    void initVars();
    void populateLayouts();
    void populateWidgets();
    void styleLayout();
    void bindButtons();

    QVBoxLayout *mainLayout;
    QWebEngineView *webView;
};

#endif