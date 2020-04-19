//
// Created by petras on 2020. 03. 13..
//

#pragma once

#include <httplib.h>
#include <QString>
#include <QMap>
#include <QObject>

#include <db_server.h>

using namespace httplib;

class Auction_db_server :public QObject{
Q_OBJECT
public:
    Auction_db_server();

    void login(const Request &request, Response &response);
    void userReg(const Request &request, Response &response);

    void search(const Request &request, Response &response);
    void auction(const Request &request, Response &response);

    void getSelf(const Request &request, Response &response);
    void getOther(const Request &request, Response &response);

    //void temp(const Request &request, Response &response);

signals:

    void check_login(const QString &user, const QString &passw, bool* ok, bool* hasError);
    void check_reg(const QString &email, const QString &user, bool* ok, bool* hasError);
    void get_self(int id, QMap<QString,QString>* data, bool* ok, bool* hasError);
    void get_other(int id, QMap<QString,QString>* data, bool* hasError);
    //void get_search(QList<int> ints, QList<QString> strings);

    void add_user(const QString &email, const QString &user, const QString &fullName, const QString &passw, const QString &add, const QString &phone, bool* hasError);

private:
    db_server* db;
};
