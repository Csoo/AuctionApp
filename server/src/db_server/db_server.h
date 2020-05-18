//
// Created by petras on 2020. 03. 24..
//

#pragma once

#include <iostream>
#include <mutex>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QThread>
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

class Db_server: public QThread {
public:

    Db_server(const QString& driver, QString connectionName, QString dbName);
    ~Db_server() override;

    bool init();

public slots:

    void check_login_slot(const QString &user, const QString &passw, int* id, bool* ok, bool* hasError);
    void check_reg_slot(const QString &email, const QString &user, bool* ok, bool* hasError);
    void get_self_slot(int id, QMap<QString,QString>* data, bool* ok, bool* hasError);
    void get_other_slot(int id, QMap<QString,QString>* data, bool* ok, bool* hasError);
    void get_search_slot(const QString &text, const QJsonDocument &filters, const QVariantList &tags, QJsonDocument *resJSON, bool *hasError);
    void get_auction_slot(int id, QJsonDocument *resJSON, bool *hasError);
    void all_auction_slot(QString *resString, bool *hasError);
    void get_id_slot(const QString &user, QString *id, bool *hasError);
    void check_bid_slot(const QString &auction, int currentP, bool *ok, bool *hasError);
    void get_close_data_slot(const QString &id, QString &lluser, QString &auuser, QString &currentP, QString &title, bool *hasError);
    void get_email_slot(const QString &user, QString &email, bool *hasError);
    void get_rate_slot(const QString &user, QString &p, QString &n, bool *hasError);

    void add_user_slot(const QString &email, const QString &user, const QString &fullName, const QString &passw, const QString &add, const QString &phone, bool* hasError);
    void add_auction_slot(const QMap<QString,QString> &parameters, const QStringList &tags, bool *hasError);
    void set_bid_slot(const QString &auction, const QString &user, int currentP, bool *hasError);
    void add_rating_slot(const QString &id, bool *hasError);
    void set_rating_slot(const QString &user, const QString &rater, const QString &positive, const QString &desc, bool *hasError);

    void get_pending_ratings_slot(int id, QJsonDocument* resJSON, bool* ok, bool* hasError);

    void read_closes_slot(QMap<QString,QString> *closes);

protected:
    std::mutex db_m;

    QSqlDatabase db;
    QString connectionName;
    QString dbName;

    QSqlQuery getLoginQuery;
    QSqlQuery checkRegQuery;
    QSqlQuery getSelfQuery;
    QSqlQuery getOtherQuery;
    QSqlQuery checkIdQuery;
    QSqlQuery getSearchQuery;
    QSqlQuery getAuctionQuery;
    QSqlQuery allAuctionQuery;
    QSqlQuery getAuctionIdQuery;
    QSqlQuery checkBidQuery;
    QSqlQuery readClosesQuery;
    QSqlQuery getCloseQuery;
    QSqlQuery getRateQuery;
    QSqlQuery getPendingRatingsQuery;

    QSqlQuery addUserQuery;
    QSqlQuery addAuctionQuery;
    QSqlQuery addRatingQuery;

    QSqlQuery updateLastQuery;
    QSqlQuery setBidQuery;
    QSqlQuery setRatingQuery;

    QDateTime now;
};