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

    void temp(const Request &request, Response &response);

signals:
    void check_login(const QString &user, const QString &passw, bool* ok, bool* hasError);

private:
    db_server* db;
};
