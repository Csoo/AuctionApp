#include "auctionimages.h"
#include <QPixmap>
#include <QString>
#include <QBuffer>
#include <QDebug>

AuctionImages::AuctionImages(QObject *parent) : QObject(parent)
{

}

void AuctionImages::addImage(const QString &source)
{
    QString sourceTrimmed = source.mid(8, -1);
    QPixmap pixmap(sourceTrimmed);
    pixmap = pixmap.scaled(750, 750, Qt::KeepAspectRatio); //what about smaller than 500x500 images?
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "JPG", 100); //min 80
    bytes.toBase64();

    qDebug() << bytes.size() << endl;

    images.push_front(bytes);
    //qDebug() << bytes.toHex() << endl;

    getImage();
}

void AuctionImages::getImage()
{
    QByteArray bytes = images.first();
    QPixmap p;
    p.loadFromData(bytes, "JPEG");
    QString name = "name"; //adatbázis id alapján kéne, legutolsó kép id + 1
    //query: select id from image order by id desc limit 1 ; ha nem működik, lehet, a limit a baj, de elvileg top 1 helyett ez van csak
    QString source = "C:\\Users\\Csongor\\Desktop\\images\\" + name + ".jpg";
    qDebug() << p.save(source, "JPEG", 80);
}

void AuctionImages::sendImage()
{

}
