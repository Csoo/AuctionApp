//
// Created by petras on 2020. 05. 09..
//

#pragma once

#include <iostream>

#include <QThread>
#include <QDateTime>
#include <QMap>

#include <cpp_email.h>

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
    void add_rating(const QString &id, bool *hasError);
    void read_closes(QMap<QString,QString> *closes);
    void get_close_data(const QString &id, QString &lluser, QString &auuser, QString &currentP, QString &title, bool *hasError);
    void get_email(const QString &user, QString &email, bool *hasError);

private:
    QMap<QString,QString> *close;
    QDateTime CT;
    QString CTS;
    Email *notification;

};
