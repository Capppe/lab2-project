#include "headers/APIhandler.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

APIHandler::APIHandler(QWidget *parent) : QWidget(parent)
{
  replies = QStringList();
}

APIHandler::~APIHandler() 
{
  qDebug() << "APIHandler destroyed";
}

QStringList APIHandler::call(QString url){
  QNetworkAccessManager *manager = new QNetworkAccessManager(this);
  QNetworkRequest request(url);
  QNetworkReply *reply = manager->get(request);

  request.setRawHeader("User-Agent", "CarHeadUnit/1.0");

  QObject::connect(manager, &QNetworkAccessManager::finished, this, &APIHandler::onApiRequestFinished);

  QHostInfo::lookupHost("all.api.radio-browser.info", this, &APIHandler::onDnsLookupFinished);

  qDebug() << "Done calling";
  return replies;
}

void APIHandler::onApiRequestFinished(QNetworkReply *reply){
  reply->deleteLater();
  if(reply->error() == QNetworkReply::NoError){
    int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "INT_V: " << v;
    if(v >= 200 && v < 300){
      QString replyText = reply->readAll();
      //qDebug() << replyText;
      serializeLanguageData(replyText);
    }else if(v >= 300 && v < 400){
      QUrl newUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
      newUrl = reply->url().resolved(newUrl);

      QNetworkAccessManager *mngr = reply->manager();
      QNetworkRequest redirection(newUrl);
      QObject::connect(mngr, &QNetworkAccessManager::finished, this, &APIHandler::onApiRequestFinished);

      return;
    }
  }else{
    qDebug() << reply->errorString();
  }
  reply->manager()->deleteLater();
}

void APIHandler::serializeLanguageData(QString jsonData){
  auto data = json::parse(jsonData.toStdString());
  std::string test;
  for (const auto& entry : data) {
    entry.at("name").get_to(test);
    replies.append(QString::fromStdString(test));
  }
  emit(this->dataRecieved(replies));
  replies.clear();
}

void APIHandler::onDnsLookupFinished(const QHostInfo &hostInfo){
  if (hostInfo.error() == QHostInfo::NoError) {
      qDebug() << "Host Name:" << hostInfo.hostName();
  } else {
      qDebug() << "DNS Lookup Error:" << hostInfo.errorString();
  }
}
