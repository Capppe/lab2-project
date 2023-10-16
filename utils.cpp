#include "headers/utils.hpp"

Utils::Utils(){}

QString Utils::getTimeFormat(qint64 milliseconds) {
    QTime time(0, 0, 0);
    time = time.addMSecs(milliseconds);
    return time.toString();
}

QList<QPair<QString, QString>> Utils::parseFileContent(QList<QString> content){
    QList<QPair<QString, QString>> contentList;

    for(const QString &c : content){
        QStringList stringList = c.split(",");
        QPair<QString, QString> newContent(stringList[0], stringList[1]);

        contentList.append(newContent);
    }

    return contentList;
}
