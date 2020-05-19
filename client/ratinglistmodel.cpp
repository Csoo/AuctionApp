#include "ratinglistmodel.h"

RatingListModel::RatingListModel(QObject *parent):
    QAbstractListModel(parent)
{

}

int RatingListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return ratings.size();
}

QVariant RatingListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case RaterId:
        return ratings.at(index.row()).getRaterId();
        break;
    case RaterUsername:
        return ratings.at(index.row()).getRaterUsername();
        break;
    case IsPositive:
        return ratings.at(index.row()).getIsPositive();
        break;
    case Description:
        return ratings.at(index.row()).getDescription();
        break;
    case RatingDate:
        return ratings.at(index.row()).getRatingDate();
        break;
    default:
        return QVariant();
        break;
    }
}

QHash<int, QByteArray> RatingListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[RaterId] = "raterId";
    names[RaterUsername] = "raterUsername";
    names[IsPositive] = "isPositive";
    names[Description] = "description";
    names[RatingDate] = "ratingDate";
    return names;
}

void RatingListModel::setRatings(int id)
{
    APIrequest req;
    ratings = req.getAllRatingsRequest(id);
}
