#ifndef AUCTIONLISTMODEL_H
#define AUCTIONLISTMODEL_H

#include <QAbstractListModel>
#include <auctionitem.h>
#include <apirequest.h>
#include <algorithm>

class AuctionListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AuctionListModel(QObject *parent = nullptr);

    enum {
        TitleRole = Qt::UserRole,
        PriceRole,
        ConditionRole,
        IdRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void sortBy(const QString &by, bool asc);
    Q_INVOKABLE void setAuctions(const QString &searchText, int category_id, const QString &color, int condition_id, int minPrice, int maxPrice, const QStringList &tags);

private:
    QVector<AuctionItem> auctions;
};

#endif // AUCTIONLISTMODEL_H
