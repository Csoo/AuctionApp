#include "auctionimages.h"
#include <QPixmap>
#include <QString>
#include <QBuffer>
#include <QDebug>

AuctionImages::AuctionImages(QObject *parent) : QObject(parent)
{

}

QByteArray AuctionImages::convertToBase64(int idx)
{
    return images.at(idx).toBase64();
}

void AuctionImages::addImage(const QString &source)
{
    QString sourceTrimmed = source.mid(8, -1);
    QPixmap pixmap(sourceTrimmed);
    pixmap = pixmap.scaled(750, 750, Qt::KeepAspectRatio);
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG", 100); //min 80
    bytes.toBase64();

    qDebug() << bytes.size() << endl;

    images.push_front(bytes);

    getImage();
}

void AuctionImages::getImage()
{
    QByteArray bytes = images.first();
    QPixmap p;
    p.loadFromData(bytes, "PNG");
    QString name = "name";
    QString source = "C:\\Users\\Csongor\\Desktop\\images\\" + name + ".png";
    qDebug() << p.save(source, "PNG", 80);
}

void AuctionImages::sendImage()
{

}
