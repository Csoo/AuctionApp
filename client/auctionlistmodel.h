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

    Q_INVOKABLE void setAuctions();

private:
    QVector<AuctionItem> auctions;
};

#endif // AUCTIONLISTMODEL_H
