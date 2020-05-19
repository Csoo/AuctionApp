#ifndef PENDINGITEMLISTMODEL_H
#define PENDINGITEMLISTMODEL_H

#include <QAbstractListModel>
#include <pendingitem.h>
#include <apirequest.h>

class PendingItemListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    PendingItemListModel(QObject *parent = nullptr);

    enum {
        RatingId = Qt::UserRole,
        UserId,
        Username,
        AuctionId,
        AuctionTitle
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setPendings(int id);

private:
    QVector<PendingItem> pendings;
};

#endif // PENDINGITEMLISTMODEL_H
