//
// Created by petras on 2020. 03. 13..
//

#include <QtCore/QString>

#include "auction_db_server.h"

void Auction_db_server::temp(const Request &request, Response &response) {

}

void Auction_db_server::login(const Request &request, Response &response) {
    response.headers = request.headers;

    QString user = "", passw = "";

    for (const auto &h: request.headers) {
        if (h.first == "user")
        {
            user = h.second.data();
            break;
        }
    }

    if (user == "")
    {
        response.status = 400;
        return;
    }

    for (const auto &h: request.headers) {
        if (h.first == "password")
        {
            passw = h.second.data();
            break;
        }
    }

    if (passw == "")
    {
        response.status = 400;
        return;
    }

    bool ok, hasError;

    db->check_login(user,passw, &ok, &hasError);

    if (hasError)
    {
        response.status = 500;
        return;
    }

    if (ok)
    {
        response.set_content("true","application/json");
    }
    else
    {
        response.set_content("false","application/json");
    }

    response.status = 200;
}

Auction_db_server::Auction_db_server() {
    db = new db_server("QSQLITE", "Auction", "../database.db");

    QObject::connect(this, &Auction_db_server::check_login, db, &db_server::check_login);

    db->start();
}
