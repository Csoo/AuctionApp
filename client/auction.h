#ifndef AUCTION_H
#define AUCTION_H

#include <QObject>
#include <apirequest.h>

class Auction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int auctionId MEMBER m_auctionId NOTIFY auctionIdChanged)
    Q_PROPERTY(int ownerUserId MEMBER ownerUserId NOTIFY ownerUserIdChanged)
    Q_PROPERTY(QString ownerUserName MEMBER m_ownerUserName NOTIFY ownerUserNameChanged)
    Q_PROPERTY(QString title MEMBER m_title NOTIFY titleChanged)
    Q_PROPERTY(QString startDate MEMBER m_startDate NOTIFY startDateChanged)
    Q_PROPERTY(QString endDate MEMBER m_endDate NOTIFY endDateChanged)
    Q_PROPERTY(int currentPrice MEMBER m_currentPrice NOTIFY currentPriceChanged)
    Q_PROPERTY(int minStep MEMBER m_minStep NOTIFY minStepChanged)
    Q_PROPERTY(int fixPrice MEMBER m_fixPrice NOTIFY fixPriceChanged)
    Q_PROPERTY(int lastLicitUserId MEMBER m_lastLicitUserId NOTIFY lastLicitUserIdChanged)
    Q_PROPERTY(QString lastLicitUserName MEMBER m_lastLicitUserName NOTIFY lastLicitUserNameChanged)
    Q_PROPERTY(QString descriptionText MEMBER m_descriptionText NOTIFY descriptionTextChanged)
    Q_PROPERTY(QString color MEMBER m_color NOTIFY colorChanged)
    Q_PROPERTY(QString conditionText MEMBER m_conditionText NOTIFY conditionTextChanged)
    Q_PROPERTY(QList<QByteArray> images MEMBER m_images NOTIFY imagesChanged)
public:
    explicit Auction(QObject *parent = nullptr);
    Q_INVOKABLE void getAuction(int id);
private:
    int m_auctionId;
    int m_ownerUserId;
    QString m_ownerUserName;
    QString m_title;
    QString m_startDate;
    QString m_endDate;
    int m_currentPrice;
    int m_minStep;
    int m_fixPrice;
    int m_lastLicitUserId;
    QString m_lastLicitUserName;
    QString m_descriptionText;
    QString m_color;
    QString m_conditionText;
    QList<QByteArray> m_images;
signals:
    void auctionIdChanged();
    void ownerUserIdChanged();
    void ownerUserNameChanged();
    void titleChanged();
    void startDateChanged();
    void endDateChanged();
    void currentPriceChanged();
    void minStepChanged();
    void fixPriceChanged();
    void lastLicitUserIdChanged();
    void lastLicitUserNameChanged();
    void descriptionTextChanged();
    void colorChanged();
    void conditionTextChanged();
    void imagesChanged();
};

#endif // AUCTION_H
