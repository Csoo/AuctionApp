#ifndef PENDINGITEM_H
#define PENDINGITEM_H

#include <QString>

class PendingItem
{
public:
    PendingItem();
    PendingItem(int ratingId, int userId, const QString &username, int auctionId, const QString &auctionTitle);
    ~PendingItem();

    int getRatingId() const;
    void setRatingId(int value);

    int getUserId() const;
    void setUserId(int value);

    QString getUsername() const;
    void setUsername(const QString &value);

    int getAuctionId() const;
    void setAuctionId(int value);

    QString getAuctionTitle() const;
    void setAuctionTitle(const QString &value);

private:
    int ratingId;
    int userId;
    QString username;
    int auctionId;
    QString auctionTitle;
};

#endif // PENDINGITEM_H
