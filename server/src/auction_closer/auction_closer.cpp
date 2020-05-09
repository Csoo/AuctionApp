//
// Created by petras on 2020. 05. 09..
//

#include "auction_closer.h"

Auction_closer::Auction_closer(QMap<QString,QString> *closes):
close(closes)
{
    moveToThread(this);
}

void Auction_closer::init() {

}
