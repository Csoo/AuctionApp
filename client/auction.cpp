#include "auction.h"

Auction::Auction(QObject *parent) : QObject(parent)
{

}

/*QJsonDocument json = QJsonDocument::fromJson("{\"auction_id\": 2, \"title\": \"valami\", \"start_date\": \"2020-04-24 10:23\", \"end_date\": \"2020-05-01 12:00\", \"current_price\": 1000, \"min_step\": 500, \"fix_price\": 5000, \"user\": [{\"last_licit_user_id\": 3, \"last_licit_user\": \"béla666\"}], \"description_text\": \"Dfnweujif wejfnwejkv nwefujh!?\", \"color\": \"hupilila\", \"condition_text\": \"használt\"}");
QJsonObject obj = json.object();
qDebug() << json.toJson();

int auctionId = obj["auction_id"].toInt();
QString title = obj["title"].toString();
QString startDate = obj["start_date"].toString();
QString endDate = obj["end_date"].toString();
int currentPrice = obj["current_price"].toInt();
int minStep = obj["min_step"].toInt();
int fixPrice = obj["fix_price"].toInt();
QString descriptionText = obj["description_text"].toString();
QString color = obj["color"].toString();
QString condition_text = obj["condition_text"].toString();
QJsonArray jsonArray = obj["user"].toArray();

QList<int> userId;
QStringList userName;

foreach (const QJsonValue & value, jsonArray) {
    QJsonObject obj = value.toObject();
    userId.append(obj["last_licit_user_id"].toInt());
    userName.append(obj["last_licit_user"].toString());
}

qDebug() << auctionId << title << startDate << endDate << currentPrice << minStep << fixPrice << descriptionText << color << condition_text;
qDebug() << userId << userName;*/
