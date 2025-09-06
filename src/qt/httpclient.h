// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020-2023 The HashmonkeyCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HASHMONKEYCOIN_HTTPCLIENT_H
#define HASHMONKEYCOIN_HTTPCLIENT_H

#include <QObject>
#include <QUrl>
#include <QString>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <string>

namespace Ui {
    class HttpClient;
}

QT_BEGIN_NAMESPACE
class QNetworkAccessManager;
QT_END_NAMESPACE

class HttpClient : public QObject {
    Q_OBJECT

public:
    explicit HttpClient(QObject* parent = nullptr);
    ~HttpClient();
    void sendFileRequest(const QUrl& url, const QString& filePath);
    void sendGetRequest(const std::string& cid, std::function<void(const QByteArray&)> callback);
//private slots:
//    void onFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* manager;
};

#endif //HASHMONKEYCOIN_HTTPCLIENT_H
