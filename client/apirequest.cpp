#include "apirequest.h"
#include <QDebug>

using json = nlohmann::json;

APIrequest::APIrequest(QObject *parent) :
    QObject(parent),
    manager(new QNetworkAccessManager(this)),
    url(QUrl("http://localhost:8080"))
{

}

bool APIrequest::loginRequest(const QString &name, const QString &pw)
{
    url.setPath("/login");
    request.setUrl(url);

    request.setRawHeader("user", name.toUtf8());
    request.setRawHeader("password", pw.toUtf8());
    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    qDebug() << url.toString() << " / " << name.toUtf8() << pw.toUtf8() << endl;

    reply = manager->get(request);
    loop.exec();

    qDebug() << reply->errorString() << endl;

    return reply->readAll() == "true";
}

bool APIrequest::registerRequest(const QString &name, const QString &pw, const QString &email, const QString &fullName, const QString &address, const QString &phone)
{
    url.setPath("/reg");
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QJsonObject regJson;
    regJson.insert("email", QJsonValue::fromVariant(email));
    regJson.insert("user", QJsonValue::fromVariant(name));
    regJson.insert("fullName", QJsonValue::fromVariant(fullName));
    regJson.insert("password", QJsonValue::fromVariant(pw));
    regJson.insert("address", QJsonValue::fromVariant(address));
    if(phone != "") regJson.insert("phone", QJsonValue::fromVariant(phone));

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->post(request, QJsonDocument(regJson).toJson());
    loop.exec();

    //qDebug() << reply->readAll() << url.toString();

    return reply->readAll() != "bad username or bad email";
}
