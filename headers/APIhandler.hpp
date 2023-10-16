#ifndef APIHANDLER_HPP
#define APIHANDLER_HPP

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>
#include <QHostInfo>
#include <QWidget>
#include <QString>
#include <QUrl>
#include <QDebug>

class APIHandler : public QWidget 
{
  Q_OBJECT
public:
  APIHandler(QWidget *parent);
  ~APIHandler();

  QStringList call(QString url);

private:
  void serializeLanguageData(QString jsonData);

  QStringList replies;
private slots:
  void onApiRequestFinished(QNetworkReply *reply);
  void onDnsLookupFinished(const QHostInfo &hostInfo);

signals:
  void dataRecieved(const QStringList &data);
};
#endif // !APIHANDLER_HPP
