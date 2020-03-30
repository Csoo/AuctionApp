#include "apirequest.h"
#include <QDebug>

using json = nlohmann::json;

APIrequest::APIrequest(QObject *parent) :
    QObject(parent),
    manager(new QNetworkAccessManager(this))
{
    request.setUrl(QUrl("localhost"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}

bool APIrequest::loginRequest(const QString &name, const QString &pw)
{
    json jsonData = {
        { "username", name.toStdString()},
        { "password", pw.toStdString()}
    };

    QString data = QString::fromStdString(jsonData.dump(4));

    reply = manager->post(request, data.toUtf8());

    return true;
}
