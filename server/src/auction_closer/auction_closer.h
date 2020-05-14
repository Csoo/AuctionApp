//
// Created by petras on 2020. 05. 09..
//

#pragma once

#include <iostream>

#include <QThread>
#include <QDateTime>
#include <QMap>

class Auction_closer : public QThread{
Q_OBJECT
public:
    explicit Auction_closer(QMap<QString,QString> *closes);
    ~Auction_closer() override;

    void closeAuction(const QString &id);

public slots:
    void server_start_slot();

signals:
    void recursion();

private:
    QMap<QString,QString> *close;
    QDateTime CT;
    QString CTS;

};
