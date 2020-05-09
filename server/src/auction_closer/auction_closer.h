//
// Created by petras on 2020. 05. 09..
//

#pragma once

#include <QThread>

class Auction_closer : public QThread{
public:
    explicit Auction_closer(QMap<QString,QString> *closes);
    void init();

private:
    QMap<QString,QString> *close;

};
