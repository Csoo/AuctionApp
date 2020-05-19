#ifndef AUCTIONIMAGES_H
#define AUCTIONIMAGES_H

#include <QObject>

class AuctionImages : public QObject
{
    Q_OBJECT
    QList<QByteArray> images;
public:
    explicit AuctionImages(QObject *parent = nullptr);
    Q_INVOKABLE QByteArray convertToBase64(int idx);
    Q_INVOKABLE void addImage(const QString &source);
    void getImage();
    Q_INVOKABLE void sendImage(int userId, const QString &title, const QString &descriptionText, const QString &color, int currentPrice, int minStep, int categoryId, int conditionId, QStringList tags, QString endDate);
    Q_INVOKABLE QList<QByteArray> getImages() const;

signals:

public slots:
};


#endif // AUCTIONIMAGES_H
