#include "headers/utils.hpp"

Utils::Utils(){}

QString Utils::getTimeFormat(qint64 milliseconds) {
    QTime time(0, 0, 0);
    time = time.addMSecs(milliseconds);
    return time.toString();
}