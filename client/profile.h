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
    Q_PROPERTY(QString lastDate MEMBER m_lastDate NOTIFY lastDateChanged)
    Q_PROPERTY(int positive MEMBER m_positive NOTIFY positiveChanged)
    Q_PROPERTY(int negative MEMBER m_negative NOTIFY negativeChanged)

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
    void lastDateChanged();
    void nameChanged();
    void positiveChanged();
    void negativeChanged();
private:
    QString m_userName;
    QString m_name;
    QString m_email;
    QString m_address;
    QString m_phone;
    QString m_regDate;
    QString m_lastDate;
    int m_positive;
    int m_negative;
};

#endif // PROFILE_H
