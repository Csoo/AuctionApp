#ifndef RATINGLISTMODEL_H
#define RATINGLISTMODEL_H

#include <QAbstractListModel>
#include <ratingitem.h>
#include <apirequest.h>

class RatingListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    RatingListModel(QObject *parent = nullptr);

    enum {
        RaterId = Qt::UserRole,
        RaterUsername,
        IsPositive,
        Description,
        RatingDate
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setRatings(int id);

private:
    QVector<RatingItem> ratings;
};

#endif // RATINGLISTMODEL_H
