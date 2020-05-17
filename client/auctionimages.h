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
    void sendImage();
signals:

public slots:
};


#endif // AUCTIONIMAGES_H
