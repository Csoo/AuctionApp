#include "apirequest.h"
#include <QDebug>

using json = nlohmann::json;

APIrequest::APIrequest(QObject *parent) :
    QObject(parent),
    manager(new QNetworkAccessManager(this)),
    url(QUrl("http://81.183.216.27:3000"))
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

    return reply->readAll() != "bad username or bad email";
}

bool APIrequest::addAuctionRequest(const QString &title, const QString &desc, const QString &color, int price, int bid, const QString &category, int conditionId, QDate endDate)
{

}

bool APIrequest::bidRequest(int auctionId, int userId, int currentPrice, int bid)
{

}

bool APIrequest::rateUserRequest(int fromUserId, int toUserId, bool isPositive, const QString &message)
{

}

QVector<AuctionItem> APIrequest::searchRequest(const QString &searchText, const QString &category, const QString &color, const QString &condition, int minPrice, int maxPrice, QStringList tags)
{
    return QVector<AuctionItem> {AuctionItem(0,"picililli","jobbmárnemislehetne",1000), AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"picililli","best",20300)};
}

QJsonDocument APIrequest::ownProfileRequest(int id)
{
     url.setPath("/user/self/" + QString::number(id));
     request.setUrl(url);

     QEventLoop loop;
     connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

     reply = manager->get(request);
     loop.exec();

     return QJsonDocument::fromJson(reply->readAll() + "\"}");
}

QJsonDocument APIrequest::profileRequest(int id)
{

}

QJsonDocument APIrequest::auctionRequest(int id)
{

}
