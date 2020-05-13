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

    m_auctionId = obj["auction_id"].toInt();
    m_ownerUserId = obj["owner_id"].toInt();
    m_ownerUserName = obj["owner"].toString();
    m_title = obj["title"].toString();
    m_startDate = obj["start_date"].toString();
    m_endDate = obj["end_date"].toString();
    m_currentPrice = obj["current_price"].toInt();
    m_minStep = obj["min_step"].toInt();
    m_fixPrice = obj["fix_price"].toInt();
    m_descriptionText = obj["description_text"].toString();
    m_color = obj["color"].toString();
    m_conditionText = obj["condition_text"].toString();

    QJsonArray jsonArray = obj["user"].toArray();

    QList<int> userId;
    QStringList userName;

    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        userId.append(obj["last_licit_user_id"].toInt());
        userName.append(obj["last_licit_user"].toString());
    }

    m_lastLicitUserid = userId.first();
    m_lastLicitUserName = userName.first();
}
