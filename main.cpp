#include "headers/mainWindow.hpp"
#include <QApplication>

int main(int argc, char **argv) {
    QApplication app (argc, argv);

    QCoreApplication::setOrganizationName("CN-Dev");
    QCoreApplication::setApplicationName("CarHeadUnit");

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}