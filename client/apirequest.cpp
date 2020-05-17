#include "apirequest.h"
#include <QDebug>

APIrequest::APIrequest(QObject *parent) :
    QObject(parent),
    manager(new QNetworkAccessManager(this)),
    url(QUrl("http://81.183.216.27:3000"))
{

}

int APIrequest::loginRequest(const QString &name, const QString &pw)
{
    url.setPath("/login");
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QJsonObject json;
    json.insert("user", QJsonValue::fromVariant(name));
    json.insert("password", QJsonValue::fromVariant(pw));

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->post(request, QJsonDocument(json).toJson());
    loop.exec();


    qDebug() << "login status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();

    QByteArray res = reply->readAll();
    qDebug() << res;
    if (res != "false" && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        if (res.isEmpty()) {
            return -1;
        }
        return res.toInt();
    }
    return -1;
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
    qDebug() << "registration status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();

    return reply->readAll() != "bad username or bad email";
}

int APIrequest::addAuctionRequest(int userId, const QString &title, const QString &descriptionText, const QString &color, int currentPrice, int minStep, int categoryId, int conditionId, QStringList tags, QDate endDate, const QList<QByteArray> &images)
{
    QJsonObject addAucJson;

    addAucJson.insert("user_id", QJsonValue::fromVariant(userId));
    addAucJson.insert("title", QJsonValue::fromVariant(title));
    addAucJson.insert("description_text", QJsonValue::fromVariant(descriptionText));
    addAucJson.insert("color", QJsonValue::fromVariant(color));
    addAucJson.insert("current_price", QJsonValue::fromVariant(currentPrice));
    addAucJson.insert("min_step", QJsonValue::fromVariant(minStep));
    addAucJson.insert("category_id", QJsonValue::fromVariant(categoryId));
    addAucJson.insert("condition_id", QJsonValue::fromVariant(conditionId));
    addAucJson.insert("tags", QJsonValue::fromVariant(tags));
    addAucJson.insert("end_date", QJsonValue::fromVariant(endDate));
    QJsonArray imageArray;
    QJsonValue img;
    for (int i = 0; i < images.length(); i++){
        img = QLatin1String(images.at(i).toBase64());
        imageArray.push_back(img);
    }
    addAucJson.insert("images", QJsonValue::fromVariant(imageArray));

    qDebug() << QJsonDocument(addAucJson).toJson();

    QByteArray res = reply->readAll();
    if (res == "false")
        return -1;
    return res.toInt();
}

int APIrequest::bidRequest(int auctionId, int licitUserId, int currentPrice, int bid)
{
    url.setPath("/bid");
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QJsonObject bidJson;

    bidJson.insert("auction_id", QJsonValue::fromVariant(auctionId));
    bidJson.insert("licit_user_id", QJsonValue::fromVariant(licitUserId));
    bidJson.insert("current_price", QJsonValue::fromVariant(currentPrice));
    bidJson.insert("bid", QJsonValue::fromVariant(bid));

    qDebug() << QJsonDocument(bidJson).toJson();

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->post(request, QJsonDocument(bidJson).toJson());
    loop.exec();

    return reply->readAll().toInt();
}

int APIrequest::rateUserRequest(int userIdFrom, int userIdTo, bool isPositive, const QString &message)
{
    url.setPath("/rate");
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QJsonObject rateJson;

    rateJson.insert("user_id_from", QJsonValue::fromVariant(userIdFrom));
    rateJson.insert("user_id_to", QJsonValue::fromVariant(userIdTo));
    rateJson.insert("positive", QJsonValue::fromVariant(isPositive)); //bool?
    rateJson.insert("message", QJsonValue::fromVariant(message));

    qDebug() << QJsonDocument(rateJson).toJson();

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->post(request, QJsonDocument(rateJson).toJson());
    loop.exec();

    QByteArray res = reply->readAll();
    if (res == "false")
        return -1;
    return res.toInt();
}

bool APIrequest::allAuctionRequest()
{

}

QVector<AuctionItem> APIrequest::searchRequest(const QString &searchText, const QString &category, const QString &color, const QString &condition, int minPrice, int maxPrice, const QStringList &tags)
{
    QVector<AuctionItem> test = {AuctionItem(1, "kutya", "new", 2120), AuctionItem(2, "macska", "bad", 212), AuctionItem(3, "kiskutya", "new", 21200), AuctionItem(4, "nagykutya", "bad", 123), AuctionItem(5, "körte", "cool", 34), AuctionItem(6, "kutya", "new", 2120), AuctionItem(7, "kutya", "newW", 120), AuctionItem(8, "alma", "new", 210)};
    return test;

    url.setPath("/search");
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QJsonObject searchJson;

    searchJson.insert("text", QJsonValue::fromVariant(searchText));
    searchJson.insert("category", QJsonValue::fromVariant(category));
    QJsonObject filterObject;
    if (color != "") searchJson.insert("color", QJsonValue::fromVariant(color));
    if (condition != "") filterObject.insert("state", QJsonValue::fromVariant(condition));
    filterObject.insert("minPrice", QJsonValue::fromVariant(minPrice));
    if (maxPrice != -1) filterObject.insert("maxPrice", QJsonValue::fromVariant(maxPrice));
    searchJson.insert("filters", filterObject);
    searchJson.insert("tags", QJsonValue::fromVariant(tags));

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->post(request, QJsonDocument(searchJson).toJson());
    loop.exec();

    qDebug() << "search status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();

    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

    QJsonArray arr = json.array();
    qDebug() << json.toJson();

    int r_auctionId;
    QString r_title;
    QString r_condition;
    int r_price;
    QVector<AuctionItem> auctionItemVector;

    foreach (QJsonValue element, arr) {
        r_auctionId = element["auction_id"].toInt();
        //qDebug() << element["auction_id"].toInt();
        r_title = element["data"][0]["title"].toString();
        //qDebug() << element["data"][0]["title"].toString();
        r_condition = element["data"][1]["condition"].toString();
        //qDebug() << element["data"][1]["condition"].toString();
        r_price = element["data"][2]["price"].toInt();
        //qDebug() << element["data"][2]["price"].toInt();
        auctionItemVector.append(AuctionItem(r_auctionId, r_title, r_condition, r_price));
    }

    return auctionItemVector;
}

QJsonDocument APIrequest::ownProfileRequest(int id)
{
     url.setPath("/user/self/" + QString::number(id));
     request.setUrl(url);

     QEventLoop loop;
     connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

     reply = manager->get(request);
     loop.exec();

     return QJsonDocument::fromJson(reply->readAll());
}

QJsonDocument APIrequest::profileRequest(int id)
{
    url.setPath("/user/" + QString::number(id));
    request.setUrl(url);

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->get(request);
    loop.exec();

    return QJsonDocument::fromJson(reply->readAll());
}

QJsonDocument APIrequest::auctionRequest(int id)
{
    url.setPath("/auction/" + QString::number(id));
    request.setUrl(url);

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->get(request);
    loop.exec();

    return QJsonDocument::fromJson(reply->readAll());
}
