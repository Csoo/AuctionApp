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

    qDebug() << json.toJson();

    m_name = obj["fullName"].toString();
    m_userName = obj["user"].toString();
    m_email = obj["email"].toString();
    m_address = obj["address"].toString();
    m_phone = obj["phone"].toString();
    m_regDate = obj["reg"].toString();
    //TODO: last_date
}

void Profile::getOtherProfile(int id)
{
    APIrequest req;
    QJsonDocument json = req.profileRequest(id);
    QJsonObject obj = json.object();

    qDebug() << json.toJson();

    m_userName = obj["user"].toString();
    m_name = obj["fullName"].toString();
    m_regDate = obj["reg"].toString();
    m_lastDate = obj["last"].toString();
}
