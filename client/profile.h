#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <apirequest.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <QDebug>

class Profile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName MEMBER m_userName NOTIFY userNameChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString email MEMBER m_email NOTIFY emailChanged)
    Q_PROPERTY(QString address MEMBER m_address NOTIFY addressChanged)
    Q_PROPERTY(QString phone MEMBER m_phone NOTIFY phoneChanged)
    Q_PROPERTY(QString regDate MEMBER m_regDate NOTIFY regDateChanged)

public:
    explicit Profile(QObject *parent = nullptr);

    Q_INVOKABLE void getOwnProfile(int id);
    Q_INVOKABLE void getOtherProfile(int id);
signals:
    void userNameChanged();
    void emailChanged();
    void addressChanged();
    void phoneChanged();
    void regDateChanged();
    void nameChanged();
private:
    QString m_userName;
    QString m_name;
    QString m_email;
    QString m_address;
    QString m_phone;
    QString m_regDate;
    QString m_lastDate;
};

#endif // PROFILE_H
