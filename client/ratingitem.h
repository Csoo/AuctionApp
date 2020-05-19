#ifndef RATINGITEM_H
#define RATINGITEM_H

#include <QString>

class RatingItem
{
public:
    RatingItem();
    RatingItem(int raterId, const QString &raterUsername, int isPositive, const QString &description, const QString &ratingDate);
    ~RatingItem();

    int getRaterId() const;
    void setRaterId(int value);

    QString getRaterUsername() const;
    void setRaterUsername(const QString &value);

    int getIsPositive() const;
    void setIsPositive(int value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getRatingDate() const;
    void setRatingDate(const QString &value);

private:
    int raterId;
    QString raterUsername;
    int isPositive;
    QString description;
    QString ratingDate;
};

#endif // RATINGITEM_H
