#ifndef AUCTIONITEM_H
#define AUCTIONITEM_H

#include <QString>

class AuctionItem {
public:
    AuctionItem();
    AuctionItem(int id, const QString &title, const QString &condition, int price);
    ~AuctionItem();

    int getPrice() const;
    void setPrice(int value);

    int getId() const;
    void setId(int value);

    QString getCondition() const;
    void setCondition(const QString &value);

    QString getTitle() const;
    void setTitle(const QString &value);

private:
    int id;
    QString title;
    QString condition;
    int price;
};

#endif // AUCTIONITEM_H
