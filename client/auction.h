#ifndef AUCTION_H
#define AUCTION_H

#include <QObject>

class Auction : public QObject
{
    Q_OBJECT
public:
    explicit Auction(QObject *parent = nullptr);

signals:

};

#endif // AUCTION_H
