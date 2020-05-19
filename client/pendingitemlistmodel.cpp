#include "pendingitemlistmodel.h"

PendingItemListModel::PendingItemListModel(QObject *parent):
    QAbstractListModel(parent)
{

}

int PendingItemListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return pendings.size();
}

QVariant PendingItemListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case RatingId:
        return pendings.at(index.row()).getRatingId();
        break;
    case UserId:
        return pendings.at(index.row()).getUserId();
        break;
    case Username:
        return pendings.at(index.row()).getUsername();
        break;
    case AuctionId:
        return pendings.at(index.row()).getAuctionId();
        break;
    case AuctionTitle:
        return pendings.at(index.row()).getAuctionTitle();
        break;
    default:
        return QVariant();
        break;
    }
}

QHash<int, QByteArray> PendingItemListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[RatingId] = "ratingId";
    names[UserId] = "userId";
    names[Username] = "username";
    names[AuctionId] = "auctionId";
    names[AuctionTitle] = "auctionTitle";
    return names;
}

void PendingItemListModel::setPendings(int id)
{
    APIrequest req;
    pendings = req.getPendingRequest(id);
    qDebug() << pendings.size();
}
