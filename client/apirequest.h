#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <3rdparty/nlohmann/json.hpp>
#include <QObject>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>

class APIrequest : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QNetworkRequest request;

    QUrl url;

public:
    explicit APIrequest(QObject *parent = nullptr);

    Q_INVOKABLE bool loginRequest(const QString &name, const QString &pw);
    Q_INVOKABLE bool registerRequest(const QString &name, const QString &pw,  const QString &email,  const QString &fullName,  const QString &address,  const QString &phone = "");
    Q_INVOKABLE

signals:

};

#endif // APIREQUEST_H
