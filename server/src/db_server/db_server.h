//
// Created by petras on 2020. 03. 24..
//

#pragma once

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
#include <iostream>

class db_server: public QThread {
public:

    db_server(const QString& driver, QString connectionName, QString dbName);
    ~db_server() override;

    bool init();

public slots:

    void check_login_slot(const QString &user, const QString &passw, bool* ok, bool* hasError);
    void check_reg_slot(const QString &email, const QString &user, bool* ok, bool* hasError);
    void get_self_slot(int id, QMap<QString,QString>* data, bool* ok, bool* hasError);
    void get_other_slot(int id, QMap<QString,QString>* data, bool* ok, bool* hasError);
    void get_search_slot(const QString &text, const QString &category, const QJsonDocument &filters, QJsonDocument *resJSON, bool *hasError);
    void get_auction_slot(int id, QJsonDocument *resJSON, bool *hasError);
    void all_auction_slot(QJsonDocument *resJSON, bool *hasError);
    void get_id_slot(const QString &user, QString *id, bool *hasError);

    void add_user_slot(const QString &email, const QString &user, const QString &fullName, const QString &passw, const QString &add, const QString &phone, bool* hasError);
    void add_auction_slot(const QMap<QString,QString> &parameters, const QStringList &tags, bool *hasError);


protected:

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

    QSqlQuery addUserQuery;
    QSqlQuery addAuctionQuery;

    QSqlQuery updateLastQuery;

    QDateTime now;
};