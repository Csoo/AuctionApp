//
// Created by petras on 2020. 03. 13..
//

#pragma once

#include <httplib.h>
#include <QString>
#include <QMap>
#include <QObject>

#include <db_server.h>
#include <auction_closer.h>

using namespace httplib;

class Auction_db_server :public QObject{
Q_OBJECT
public:
    explicit Auction_db_server(const QString &route);

    void login(const Request &request, Response &response);
    void userReg(const Request &request, Response &response);

    void search(const Request &request, Response &response);

    void addAuction(const Request &request, Response &response);
    void auction(const Request &request, Response &response);
    void allAuction(const Request &request, Response &response);

    void getSelf(const Request &request, Response &response);
    void getOther(const Request &request, Response &response);

    void bid(const Request &request, Response &response);
    void rate(const Request &request, Response &response);

    void getPendingRatings(const Request &request, Response &response);

    //void temp(const Request &request, Response &response);

signals:

    void check_login(const QString &user, const QString &passw, int* id, bool* ok, bool* hasError);
    void check_reg(const QString &email, const QString &user, bool* ok, bool* hasError);
    void get_self(int id, QMap<QString,QString>* data, bool* ok, bool* hasError);
    void get_other(int id, QMap<QString,QString>* data, bool* ok, bool* hasError);
    void get_search(const QString &text, const QJsonDocument &filters, const QVariantList &tags, QJsonDocument *resJSON, bool *hasError);
    void get_auction(int id, QJsonDocument *resJSON, bool *hasError);
    void all_auction(QJsonDocument *resJSON, bool *hasError);
    void get_id(const QString &user, QString *id, bool *hasError);
    void check_bid(const QString &auction, int currentP, bool *ok, bool *hasError);
    void get_rate(const QString &user, QString &p, QString &n, bool *hasError);

    void add_user(const QString &email, const QString &user, const QString &fullName, const QString &passw, const QString &add, const QString &phone, bool* hasError);
    void add_auction(const QMap<QString,QString> &parameters, const QStringList &tags, bool *hasError);
    void set_bid(const QString &auction, const QString &user, int currentP, bool *hasError);
    void set_rating(const QString &user, const QString &rater, const QString &positive, const QString &desc, bool *hasError);

    void get_pending_ratings(int id, QJsonDocument* resJSON, bool* ok, bool* hasError);

    void server_start();

public:
    QMap<QString,QString> *closes;

private:
    Db_server* db;
    Auction_closer* closer;
};
