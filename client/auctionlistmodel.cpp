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
    case IdRole:
        return auctions.at(index.row()).getId();
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
    names[IdRole] = "id";
    return names;
}

void AuctionListModel::sortBy(const QString &by, bool asc)
{
    beginResetModel();
    if (by == "price")
        std::sort(auctions.begin(), auctions.end(), [asc](const AuctionItem &a, const AuctionItem &b)->bool{if(asc) return a.getPrice() < b.getPrice(); return a.getPrice() > b.getPrice();});
    else
        std::sort(auctions.begin(), auctions.end(), [asc](const AuctionItem &a, const AuctionItem &b)->bool{if(asc) return a.getTitle().toLower() < b.getTitle().toLower(); return a.getTitle().toLower() > b.getTitle().toLower();});
    endResetModel();
}

void AuctionListModel::setAuctions(const QString &searchText, int category_id, const QString &color, int condition_id, int minPrice, int maxPrice, const QStringList &tags)
{
    beginResetModel();
    APIrequest req;
    auctions = req.searchRequest(searchText, category_id, color, condition_id, minPrice, maxPrice, tags);
    endResetModel();
}
