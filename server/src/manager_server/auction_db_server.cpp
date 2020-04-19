//
// Created by petras on 2020. 03. 13..
//

#include <QString>
#include <QJsonDocument>
#include <QJsonArray>

#include "auction_db_server.h"

//void Auction_db_server::temp(const Request &request, Response &response) {
//
//}

Auction_db_server::Auction_db_server() {
    db = new db_server("QSQLITE", "Auction", "./database.db");
    db->init();

    QObject::connect(this, &Auction_db_server::check_login, db, &db_server::check_login_slot, Qt::ConnectionType::QueuedConnection);
    QObject::connect(this, &Auction_db_server::check_reg, db, &db_server::check_reg_slot, Qt::ConnectionType::QueuedConnection);
    QObject::connect(this, &Auction_db_server::add_user, db, &db_server::add_user_slot, Qt::ConnectionType::QueuedConnection);
    QObject::connect(this, &Auction_db_server::get_self, db, &db_server::get_self_slot, Qt::ConnectionType::QueuedConnection);
    QObject::connect(this, &Auction_db_server::get_other, db, &db_server::get_other_slot, Qt::ConnectionType::QueuedConnection);

    db->start();
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

    emit check_login(user,passw, &ok, &hasError);

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

void Auction_db_server::userReg(const Request &request, Response &response) {
    response.headers = request.headers;

    if (request.headers.find("content_type") == request.headers.end())
    {
        response.status = 400;
        return;
    }

    QString email, user, fullName, passw, add, phone;

    QJsonDocument body = QJsonDocument::fromJson(request.body.c_str());

    try
    {
        email = body["email"].toString();
        user = body["user"].toString();
        fullName = body["fullName"].toString();
        passw = body["password"].toString();
        add = body["address"].toString();
    }
    catch (...)
    {
        response.status = 400;
        return;
    }

    if (body["phone"] != "")
    {
        phone = body["phone"].toString();
    }

    bool ok, hasError;

    emit check_reg(email, user, &ok, &hasError);

    if (hasError)
    {
        response.status = 500;
        return;
    }

    if (!ok)
    {
        emit add_user(email, user, fullName, passw, add, phone, &hasError);
    }

    if (ok == 1)
    {
        response.set_content("bad username or bad email","application/json");
        response.status = 400;
        return;
    }

    if (hasError)
    {
        response.status = 500;
        return;
    }

    response.status = 200;
}

void Auction_db_server::search(const Request &request, Response &response) {
    response.headers = request.headers;

    if (request.headers.find("content_type") == request.headers.end())
    {
        response.status = 400;
        return;
    }

    QString text;
    QJsonArray filters;

    QJsonDocument body = QJsonDocument::fromJson(request.body.c_str());

    try
    {
        text = body["text"].toString();
        filters = body["filters"].toArray();
    }
    catch (...)
    {
        response.status = 400;
        return;
    }

    //todo: logic for parameterize qsl query

    response.status = 200;
}

void Auction_db_server::auction(const Request &request, Response &response) {
    QString auId = QString::fromStdString(request.matches[1].str());

    int id = auId.toInt();

    bool ok, hasError;

    //todo: signal emit

    if (hasError)
    {
        response.status = 500;
        return;
    }

    //todo: normal response

    response.status = 200;
}

void Auction_db_server::getSelf(const Request &request, Response &response) {
    QString auId = QString::fromStdString(request.matches[1].str());

    int id = auId.toInt();

    bool ok, hasError;
    QMap<QString,QString> data;

    emit get_self(id, &data, &ok, &hasError);

    if (hasError)
    {
        response.status = 500;
        return;
    }

    if (!ok)
    {
        response.status = 404;
        return;
    }

    QString body = R"({"email":")" + data["email"]
                + R"(","user":")" + data["user"]
                + R"(","fullName":")" + data["fullName"]
                + R"(","address":")" + data["address"]
                + R"(","phone":")" + data["phone"]
                + R"(","reg":")" + data["reg"];


        response.set_content(body.toStdString(),"application/json");

    response.status = 200;
}

void Auction_db_server::getOther(const Request &request, Response &response) {
    QString auId = QString::fromStdString(request.matches[1].str());

    int id = auId.toInt();

    bool hasError;
    QMap<QString,QString> data;

    emit get_other(id, &data, &hasError);

    if (hasError)
    {
        response.status = 500;
        return;
    }

    QString body = R"(","user":")" + data["user"]
                   + R"(","fullName":")" + data["fullName"]
                   + R"(","reg":")" + data["reg"];
    + R"(","last":")" + data["last"];


    response.set_content(body.toStdString(),"application/json");

    response.status = 200;
}
