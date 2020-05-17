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

    m_auctionId = obj["auction_id"].toVariant().Int;
    m_ownerUserId = obj["owner_id"].toVariant().Int;
    m_ownerUserName = obj["owner"].toString();
    m_title = obj["title"].toString();
    m_startDate = obj["start_date"].toString();
    m_endDate = obj["end_date"].toString();
    m_currentPrice = obj["current_price"].toVariant().Int;
    m_minStep = obj["min_step"].toVariant().Int;
    m_fixPrice = obj["fix_price"].toVariant().Int;
    m_descriptionText = obj["description_text"].toString();
    m_color = obj["description_color"].toString();
    m_conditionText = obj["condition_text"].toString();

    QJsonArray jsonArray = obj["user"].toArray();
    QJsonArray imagesArray = obj["images"].toArray();

    QList<int> userId;
    QStringList userName;
    QList<QByteArray> images;

    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        userId.append(obj["last_licit_user_id"].toInt());
        userName.append(obj["last_licit_user"].toString());
    }

    foreach (const QJsonValue & value, jsonArray) {
        images.push_back(value.toString().toLatin1());
        // auto byteImg = value.toString().toLatin1();
        // images.push_back(QByteArray::fromBase64(byteImg));
    }

    m_lastLicitUserId = userId.first();
    m_lastLicitUserName = userName.first();
    m_images = images;

    qDebug() << m_currentPrice << "/n";
}
