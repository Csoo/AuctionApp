#include "apirequest.h"
#include <QDebug>

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

int APIrequest::addAuctionRequest(int userId, const QString &title, const QString &descriptionText, const QString &color, int currentPrice, int minStep, int categoryId, int conditionId, QStringList tags, QDate endDate)
{
    QJsonObject regJson;

    regJson.insert("user_id", QJsonValue::fromVariant(userId));
    regJson.insert("title", QJsonValue::fromVariant(title));
    regJson.insert("description_text", QJsonValue::fromVariant(descriptionText));
    regJson.insert("color", QJsonValue::fromVariant(color));
    regJson.insert("current_price", QJsonValue::fromVariant(currentPrice));
    regJson.insert("min_step", QJsonValue::fromVariant(minStep));
    regJson.insert("category_id", QJsonValue::fromVariant(categoryId));
    regJson.insert("condition_id", QJsonValue::fromVariant(conditionId));
    regJson.insert("tags", QJsonValue::fromVariant(tags));
    regJson.insert("end_date", QJsonValue::fromVariant(endDate));

    qDebug() << QJsonDocument(regJson).toJson();

    return -1; //vagy auctionId
}

bool APIrequest::bidRequest(int auctionId, int licitUserId, int currentPrice, int bid)
{
    QJsonObject regJson;

    regJson.insert("auction_id", QJsonValue::fromVariant(auctionId));
    regJson.insert("licit_user_id", QJsonValue::fromVariant(licitUserId));
    regJson.insert("current_price", QJsonValue::fromVariant(currentPrice));
    regJson.insert("bid", QJsonValue::fromVariant(bid));

    qDebug() << QJsonDocument(regJson).toJson();

    return false;
}

bool APIrequest::rateUserRequest(int userIdFrom, int userIdTo, bool isPositive, const QString &message)
{
    QJsonObject regJson;
    regJson.insert("user_id_from", QJsonValue::fromVariant(userIdFrom));
    regJson.insert("user_id_to", QJsonValue::fromVariant(userIdTo));
    regJson.insert("positive", QJsonValue::fromVariant(isPositive)); //bool?
    regJson.insert("message", QJsonValue::fromVariant(message));

    qDebug() << QJsonDocument(regJson).toJson();

    return false;
}

bool APIrequest::allAuctionRequest()
{

}

QVector<AuctionItem> APIrequest::searchRequest(const QString &searchText, const QString &category, const QString &color, const QString &condition, int minPrice, int maxPrice, QStringList tags)
{     
    /*QJsonDocument json = QJsonDocument::fromJson("[{\"auction_id\": 7, \"data\": [{\"title\": \"Ez egy kék lapát\"}, {\"condition\": \"használt\"}, {\"price\": 400}]}, {\"auction_id\": 3, \"data\": [{\"title\": \"Ez egy másik lapát\"}, {\"condition\": \"új\"}, {\"price\": 1000}]}]");
    QJsonArray arr = json.array();
    qDebug() << json.toJson();

    QList<int> auctionIdList;
    QStringList titleList;
    QStringList conditionList;
    QList<int> priceList;

    foreach (QJsonValue element, arr) {
        auctionIdList.append(element["auction_id"].toInt());
        //qDebug() << element["auction_id"].toInt();
        titleList.append(element["data"][0]["title"].toString());
        //qDebug() << element["data"][0]["title"].toString();
        conditionList.append(element["data"][1]["condition"].toString());
        //qDebug() << element["data"][1]["condition"].toString();
        priceList.append(element["data"][2]["price"].toInt());
        //qDebug() << element["data"][2]["price"].toInt();
    }
    qDebug() << auctionIdList << titleList << conditionList << priceList;*/


    return QVector<AuctionItem> {AuctionItem(0,"Termék","jobbmárnemislehetne",1000), AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300),AuctionItem(2,"bojler","best",20300)};
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
