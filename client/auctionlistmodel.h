#ifndef AUCTIONLISTMODEL_H
#define AUCTIONLISTMODEL_H

#include <QAbstractListModel>
#include <auctionitem.h>
#include <apirequest.h>

class AuctionListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AuctionListModel(QObject *parent = nullptr);

    enum {
        TitleRole = Qt::UserRole,
        PriceRole,
        ConditionRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setAuctions(const QString &searchText, const QString &category, const QString &color, const QString &condition, int minPrice, int maxPrice, const QStringList &tags);

private:
    QVector<AuctionItem> auctions;
};

#endif // AUCTIONLISTMODEL_H
