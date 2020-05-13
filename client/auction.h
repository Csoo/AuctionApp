#ifndef AUCTION_H
#define AUCTION_H

#include <QObject>
#include <apirequest.h>

class Auction : public QObject
{
    Q_OBJECT
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
    int m_lastLicitUserid;
    QString m_lastLicitUserName;
    QString m_descriptionText;
    QString m_color;
    QString m_conditionText;
signals:

};

#endif // AUCTION_H
