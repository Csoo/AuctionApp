#include "ratingitem.h"

RatingItem::RatingItem()
{

}

RatingItem::RatingItem(int raterId, const QString &raterUserName, int isPositive, const QString &description, const QString &ratingDate):
    raterId(raterId),
    raterUsername(raterUserName),
    isPositive(isPositive),
    description(description),
    ratingDate(ratingDate)
{

}

RatingItem::~RatingItem()
{

}

int RatingItem::getRaterId() const
{
    return raterId;
}

void RatingItem::setRaterId(int value)
{
    raterId = value;
}

QString RatingItem::getRaterUsername() const
{
    return raterUsername;
}

void RatingItem::setRaterUsername(const QString &value)
{
    raterUsername = value;
}

int RatingItem::getIsPositive() const
{
    return isPositive;
}

void RatingItem::setIsPositive(int value)
{
    isPositive = value;
}

QString RatingItem::getDescription() const
{
    return description;
}

void RatingItem::setDescription(const QString &value)
{
    description = value;
}

QString RatingItem::getRatingDate() const
{
    return ratingDate;
}

void RatingItem::setRatingDate(const QString &value)
{
    ratingDate = value;
}
