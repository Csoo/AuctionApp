//
// Created by petras on 2020. 05. 09..
//

#include "auction_closer.h"

Auction_closer::Auction_closer(QMap<QString,QString> *closes):
close(closes)
{
    CT = QDateTime::currentDateTime();

    QObject::connect(this, &Auction_closer::recursion, this, &Auction_closer::server_start_slot, Qt::ConnectionType::QueuedConnection);

    std::cout << "[Auction_closer] Log: Started" << std::endl;

    emit read_closes(closes);

    std::cout << "[Auction_closer] Log: Closes read" << std::endl;

    moveToThread(this);
}

void Auction_closer::server_start_slot() {
    while (CT.time().toString(Qt::ISODate).mid(2,3) != "00") {
        this->thread()->sleep(60);

        CT = QDateTime::currentDateTime();
        std::cout << "[Auction_closer] Log: Sync minutes" << std::endl;
    }

    while (CT.time().toString(Qt::ISODate).mid(-1,3) != "00") {
        this->thread()->sleep(3600);

        CT = QDateTime::currentDateTime();
        std::cout << "[Auction_closer] Log: Sync hours" << std::endl;
    }

    //'YYYY-MM-DD HH:MM' - date format in string -- Qt::ISODate (0-10) + Qt::ISODate (0-5)
    CTS = CT.toString(Qt::ISODate).mid(-1,11) + " " + CT.time().toString(Qt::ISODate).mid(-1,6);

    std::cout << "[Auction_closer] Log: Check close list" << std::endl;
    for (const auto& p : *close) {
        if (p <= CTS)
        {
            closeAuction(close->key(p));
        }
    }

    this->thread()->sleep(82800);

    emit recursion();
}

Auction_closer::~Auction_closer() {
    quit();
    wait();
    moveToThread(nullptr);
}

void Auction_closer::closeAuction(const QString &id) {

    std::cout << "[Auction_closer] Log: Auction " + id.toStdString() + " closed" << std::endl;

    bool hasError;

    emit add_rating(id, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_closer] Error: From Db_server" << id.toStdString() << " auction closing failed on add_rating"<< std::endl;
        return;
    }

    close->remove(id);
}
