#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <3rdparty/nlohmann/json.hpp>
#include <QObject>

class APIrequest : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QNetworkRequest request;

public:
    explicit APIrequest(QObject *parent = nullptr);

    Q_INVOKABLE bool loginRequest(const QString &name, const QString &pw);

signals:

};

#endif // APIREQUEST_H
