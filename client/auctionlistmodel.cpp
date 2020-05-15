#include "auctionlistmodel.h"

AuctionListModel::AuctionListModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int AuctionListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return auctions.size();
}

QVariant AuctionListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case TitleRole:
        return auctions.at(index.row()).getTitle();
        break;
    case PriceRole:
        return auctions.at(index.row()).getPrice();
        break;
    case ConditionRole:
        return auctions.at(index.row()).getCondition();
        break;
    default:
        return QVariant();
        break;
    }
}

QHash<int, QByteArray> AuctionListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TitleRole] = "title";
    names[PriceRole] = "price";
    names[ConditionRole] = "condition";
    return names;
}

void AuctionListModel::setAuctions(const QString &searchText, const QString &category, const QString &color, const QString &condition, int minPrice, int maxPrice, const QStringList &tags)
{
    APIrequest req;
    auctions = req.searchRequest(searchText, category, color, condition, minPrice, maxPrice, tags);
}
