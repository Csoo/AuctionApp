#include "profile.h"

Profile::Profile(QObject *parent):
    QObject(parent)
{
    
}

void Profile::getOwnProfile(int id)
{
    APIrequest req;
    QJsonDocument json = req.ownProfileRequest(id);
    QJsonObject obj = json.object();

    //QJsonDocument json = QJsonDocument::fromJson("{\"user\": \"bela\", \"fullName\": \"Kiss Bela\", \"address\": \"1234 Kiskunhalas, Kalap u. 13/A\", \"phone\": \"06123456\", \"reg\": \"2020-05-01 10:00\"}");
    //QJsonObject obj = json.object();
    //qDebug() << json.toJson();

    /*QString userName = obj["user"].toString();
    QString fullName = obj["fullName"].toString();
    QString address = obj["address"].toString();
    QString phone = obj["phone"].toString(); //ez opcionalis
    QString regDate = obj["reg"].toString();
    qDebug() << userName << fullName << address << phone << regDate;*/

    qDebug() << json.toJson();

    m_name = obj["fullName"].toString();
    m_userName = obj["user"].toString();
    m_email = obj["email"].toString();
    m_address = obj["address"].toString();
    m_phone = obj["phone"].toString();
    m_regDate = obj["reg"].toString();
}
