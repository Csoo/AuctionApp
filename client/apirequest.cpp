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
    qDebug("Sending login request.");
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

    if (res != "false") {
        if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
            if (res.isEmpty()) {
                return -1;
            }
            return res.toInt();
        } else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == NULL) {
            if (res.isEmpty()) {
                return -2;
            }
            return res.toInt();
        }
    }

//    if (res != "false" && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
//        if (res.isEmpty()) {
//            return -1;
//        }
//        return res.toInt();
//    }
    return -1;
}

bool APIrequest::registerRequest(const QString &name, const QString &pw, const QString &email, const QString &fullName, const QString &address, const QString &phone)
{
    qDebug("Sending registration request.");
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

int APIrequest::addAuctionRequest(int userId, const QString &title, const QString &descriptionText, const QString &color, int currentPrice, int minStep, int categoryId, int conditionId, QStringList tags, QString endDate, const QList<QByteArray> &images)
{
    qDebug("Sending addAuction request.");
    url.setPath("/auction");
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QJsonObject addAucJson;

    addAucJson.insert("user_id", QJsonValue::fromVariant(userId));
    addAucJson.insert("title", QJsonValue::fromVariant(title));
    addAucJson.insert("description_text", QJsonValue::fromVariant(descriptionText));
    addAucJson.insert("color", QJsonValue::fromVariant(color));
    addAucJson.insert("current_price", QJsonValue::fromVariant(currentPrice));
    addAucJson.insert("min_step", QJsonValue::fromVariant(minStep));
    addAucJson.insert("category_id", QJsonValue::fromVariant(categoryId));
    addAucJson.insert("condition_id", QJsonValue::fromVariant(conditionId));
    addAucJson.insert("end_date", QJsonValue::fromVariant(endDate));
    QJsonArray tagsArray;
    foreach (QString tag, tags) {
        tagsArray.push_back(QJsonValue(tag));
    }
    addAucJson.insert("tags",QJsonValue(tagsArray));
    QJsonArray imageArray;
    QJsonValue img;
    for (int i = 0; i < images.length(); i++){
        img = QLatin1String(images[i].toBase64());
        imageArray.push_back(img);
    }
    addAucJson.insert("images", QJsonValue(imageArray));


    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->post(request, QJsonDocument(addAucJson).toJson());
    loop.exec();

    qDebug() << "add auction status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();

    QByteArray res = reply->readAll();
    if (res == "false")
        return -1;
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
        return res.toInt();
    return -1;
}

int APIrequest::bidRequest(int auctionId, int licitUserId, int currentPrice, int bid)
{
    qDebug("Sending bid request.");
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


    qDebug() << "search status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();

    return reply->readAll().toInt();
}

int APIrequest::rateUserRequest(int rateId, bool isPositive, const QString &message)
{
    qDebug("Sending rate request.");
    url.setPath("/rate");
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QJsonObject rateJson;

    rateJson.insert("rateId", QJsonValue::fromVariant(rateId));
    rateJson.insert("positive", QJsonValue::fromVariant(isPositive)); //bool?
    rateJson.insert("message", QJsonValue::fromVariant(message));

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->post(request, QJsonDocument(rateJson).toJson());
    loop.exec();


    qDebug() << "rate status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();

    QByteArray res = reply->readAll();
    if (res == "false")
        return -1;
    return res.toInt();
}

bool APIrequest::allAuctionRequest()
{

}

QVector<AuctionItem> APIrequest::searchRequest(const QString &searchText, int category_id, const QString &color, int condition_id, int minPrice, int maxPrice, const QStringList &tags)
{
    qDebug("Sending search request.");

    url.setPath("/search");
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QJsonObject searchJson;

    searchJson.insert("text", QJsonValue::fromVariant(searchText));
    QJsonObject filterObject;
    if (category_id > 0) filterObject.insert("category_id", QJsonValue::fromVariant(category_id));
    if (color != "") filterObject.insert("color", QJsonValue::fromVariant(color));
    if (condition_id > 0) filterObject.insert("condition_id", QJsonValue::fromVariant(condition_id));
    filterObject.insert("minPrice", QJsonValue::fromVariant(minPrice));
    if (maxPrice != -1) filterObject.insert("maxPrice", QJsonValue::fromVariant(maxPrice));
    searchJson.insert("filters", filterObject);
    tags[0].isEmpty() ? searchJson.insert("tags", QJsonValue("[]")) : searchJson.insert("tags", QJsonValue::fromVariant(tags));

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->post(request, QJsonDocument(searchJson).toJson());
    loop.exec();

    qDebug() << "search status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();

    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

    QJsonArray arr = json.array();

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
        r_condition = element["data"][0]["condition"].toString();
        //qDebug() << element["data"][1]["condition"].toString();
        r_price = element["data"][0]["price"].toInt();
        //qDebug() << element["data"][2]["price"].toInt();
        auctionItemVector.append(AuctionItem(r_auctionId, r_title, r_condition, r_price));
    }

    return auctionItemVector;
}

QJsonDocument APIrequest::ownProfileRequest(int id)
{
     qDebug("Sending selfProfile request.");
     url.setPath("/user/self/" + QString::number(id));
     request.setUrl(url);

     QEventLoop loop;
     connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

     reply = manager->get(request);
     loop.exec();


     qDebug() << "search selfProfile:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();

     return QJsonDocument::fromJson(reply->readAll());
}

QJsonDocument APIrequest::profileRequest(int id)
{
    qDebug("Sending getUserProfile request.");
    url.setPath("/user/" + QString::number(id));
    request.setUrl(url);

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->get(request);
    loop.exec();

    qDebug() << "profile status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();

    return QJsonDocument::fromJson(reply->readAll());
}

QJsonDocument APIrequest::auctionRequest(int id)
{
    qDebug("Sending getAuction request.");
    url.setPath("/auction/" + QString::number(id));
    request.setUrl(url);

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->get(request);
    loop.exec();

    qDebug() << "auction status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();

    return QJsonDocument::fromJson(reply->readAll());
}

QVector<PendingItem> APIrequest::getPendingRequest(int id)
{
    qDebug("Sending getPendingRequest request.");
    url.setPath("/pending/" + QString::number(id));
    request.setUrl(url);

    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->get(request);
    loop.exec();

    qDebug() << "pending rating status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();


    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    QJsonArray arr = json.array();

    int r_ratingId;
    int r_userId;
    QString r_username;
    int r_auctionId;
    QString r_auctionTitle;
    QVector<PendingItem> pendingItemVector;

    foreach (QJsonValue element, arr) {
        r_ratingId = element["ratingId"].toString().toInt();
        r_userId = element["userId"].toString().toInt();
        r_username = element["userName"].toString();
        r_auctionId = element["auctionId"].toString().toInt();
        r_auctionTitle = element["auctionTitle"].toString();
        pendingItemVector.append(PendingItem(r_ratingId, r_userId, r_username, r_auctionId, r_auctionTitle));
    }

    return pendingItemVector;
}

QVector<RatingItem> APIrequest::getAllRatingsRequest(int id)
{
    qDebug("Sending getAllRatings request.");
    url.setPath("/ratings/" + QString::number(id));
    request.setUrl(url);


    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    reply = manager->get(request);
    loop.exec();

    qDebug() << "rating status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();

    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    QJsonArray arr = json.array();

    int r_raterId;
    QString r_raterUsername;
    int r_isPositive;
    QString r_description;
    QString r_ratingDate;
    QVector<RatingItem> ratingItemVector;

    foreach (QJsonValue element, arr) {
        r_raterId = element["rater_id"].toString().toInt();
        r_raterUsername = element["rater_username"].toString();
        r_isPositive = element["is_positive"].toString().toInt();
        r_description = element["description"].toString();
        r_ratingDate = element["rating_date"].toString();
        ratingItemVector.append(RatingItem(r_raterId, r_raterUsername, r_isPositive, r_description, r_ratingDate));
    }

    return ratingItemVector;
}
