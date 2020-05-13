#include "auctionitem.h"

AuctionItem::AuctionItem(int id, const QString &title, const QString &condition, int price):
    id(id),
    title(title),
    condition(condition),
    price(price)
{

}

AuctionItem::~AuctionItem()
{

}

int AuctionItem::getPrice() const
{
    return price;
}

void AuctionItem::setPrice(int value)
{
    price = value;
}

int AuctionItem::getId() const
{
    return id;
}

void AuctionItem::setId(int value)
{
    id = value;
}

QString AuctionItem::getCondition() const
{
    return condition;
}

void AuctionItem::setCondition(const QString &value)
{
    condition = value;
}

QString AuctionItem::getTitle() const
{
    return title;
}

void AuctionItem::setTitle(const QString &value)
{
    title = value;
}
