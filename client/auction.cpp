#include "auction.h"

Auction::Auction(QObject *parent) : QObject(parent)
{

}

void Auction::getAuction(int id)
{
    APIrequest req;
    QJsonDocument json = req.auctionRequest(id);
    QJsonObject obj = json.object();

    qDebug() << json.toJson();

    m_auctionId = obj["auction_id"].toString().toInt();
    m_ownerUserId = obj["owner_id"].toString().toInt();
    m_ownerUserName = obj["owner"].toString();
    m_title = obj["title"].toString();
    m_startDate = obj["start_date"].toString();
    m_endDate = obj["end_date"].toString();
    m_currentPrice = obj["current_price"].toString().toInt();
    m_minStep = obj["min_step"].toString().toInt();
    m_fixPrice = obj["fix_price"].toString().toInt();
    m_descriptionText = obj["description_text"].toString();
    m_color = obj["description_color"].toString();
    m_conditionText = obj["condition_text"].toString();

    QJsonArray imagesArray = obj["images"].toArray();

    if (!obj["user"].isNull()) {
        QJsonArray userArray = obj["user"].toArray();
        QList<int> userId;
        QStringList userName;
        foreach (const QJsonValue & value, userArray) {
            QJsonObject obj = value.toObject();
            userId.append(obj["last_licit_user_id"].toString().toInt());
            userName.append(obj["last_licit_user"].toString());
        }
        m_lastLicitUserId = userId.first();
        m_lastLicitUserName = userName.first();
        qDebug() << m_lastLicitUserId << m_lastLicitUserName;
    } else {
        m_lastLicitUserId = -1;
        m_lastLicitUserName = "";
        qDebug() << m_lastLicitUserId << m_lastLicitUserName;
    }

    QList<QByteArray> images;

    images.clear();
    foreach (const QJsonValue & value, imagesArray) {
        images.push_back(value.toString().toLatin1());
        // auto byteImg = value.toString().toLatin1();
        // images.push_back(QByteArray::fromBase64(byteImg));
    }

    m_images = images;

    qDebug() << m_currentPrice << "/n";
}
