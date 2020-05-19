#include "auctionimages.h"
#include <QPixmap>
#include <QString>
#include <QBuffer>
#include <QDebug>
#include <apirequest.h>

QList<QByteArray> AuctionImages::getImages() const
{
    return images;
}

QByteArray AuctionImages::convertToBase64(int i)
{

}

AuctionImages::AuctionImages(QObject *parent) : QObject(parent)
{

}

void AuctionImages::addImage(const QString &source)
{
    QString sourceTrimmed = source.mid(8, -1);
    QPixmap pixmap(sourceTrimmed);
    pixmap = pixmap.scaled(1000, 1000, Qt::KeepAspectRatio);
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "JPG", 100); //min 80
    bytes.toBase64();

    qDebug() << bytes.size() << endl;

    images.push_front(bytes);
}

int AuctionImages::sendImage(int userId, const QString &title, const QString &descriptionText, const QString &color, int currentPrice, int minStep, int categoryId, int conditionId, QStringList tags, QString endDate)
{
    int response;
    APIrequest req;
    response = req.addAuctionRequest(userId, title, descriptionText, color, currentPrice, minStep, categoryId, conditionId, tags, endDate, images);

    images.clear();
    return response;
}
