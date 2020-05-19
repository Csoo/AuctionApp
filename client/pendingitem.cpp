#include "pendingitem.h"

PendingItem::PendingItem()
{

}

PendingItem::PendingItem(int ratingId, int userId, const QString &username, int auctionId, const QString &auctionTitle):
    ratingId(ratingId),
    userId(userId),
    username(username),
    auctionId(auctionId),
    auctionTitle(auctionTitle)
{

}

int PendingItem::getRatingId() const
{
    return ratingId;
}

void PendingItem::setRatingId(int value)
{
    ratingId = value;
}

int PendingItem::getUserId() const
{
    return userId;
}

void PendingItem::setUserId(int value)
{
    userId = value;
}

QString PendingItem::getUsername() const
{
    return username;
}

void PendingItem::setUsername(const QString &value)
{
    username = value;
}

int PendingItem::getAuctionId() const
{
    return auctionId;
}

void PendingItem::setAuctionId(int value)
{
    auctionId = value;
}

QString PendingItem::getAuctionTitle() const
{
    return auctionTitle;
}

void PendingItem::setAuctionTitle(const QString &value)
{
    auctionTitle = value;
}
