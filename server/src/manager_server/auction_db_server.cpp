//
// Created by petras on 2020. 03. 13..
//

#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <iostream>

#include "auction_db_server.h"

//void Auction_db_server::temp(const Request &request, Response &response) {
//
//}

Auction_db_server::Auction_db_server() {
    db = new db_server("QSQLITE", "Auction", "./database.db");
    db->init();

    QObject::connect(this, &Auction_db_server::check_login, db, &db_server::check_login_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::check_reg, db, &db_server::check_reg_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::add_user, db, &db_server::add_user_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::get_self, db, &db_server::get_self_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::get_other, db, &db_server::get_other_slot, Qt::ConnectionType::BlockingQueuedConnection);

    db->start();
}

void Auction_db_server::login(const Request &request, Response &response) {
    response.headers = request.headers;

    std::cout << "login section\n";
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
    std::cout << "user ok\n";
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
    std::cout << "password ok\n";
    bool ok, hasError;
    std::cout << "check start\n";
    emit check_login(user,passw, &ok, &hasError);
    std::cout << "check end\n";
    if (hasError)
    {
        std::cout << "err\n";
        response.status = 500;
        return;
    }

    if (ok)
    {
        std::cout << "true\n";
        response.set_content("true","application/json");
    }
    else
    {
        std::cout << "false\n";
        response.set_content("false","application/json");
    }
    std::cout << "return\n";
    response.status = 200;
}

void Auction_db_server::userReg(const Request &request, Response &response) {
    response.headers = request.headers;

    std::cout << "reg section\n";
    if (request.headers.find("Content-Type") == request.headers.end())
    {
        response.status = 400;
        return;
    }
    std::cout << "content type ok\n";
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
    std::cout << "data ok\n";
    if (body["phone"] != "")
    {
        phone = body["phone"].toString();
    }
    std::cout << "phone ok\n";
    bool ok, hasError;
    std::cout << "reg check start\n";
    emit check_reg(email, user, &ok, &hasError);
    std::cout << "reg check end\n";
    if (hasError)
    {
        response.status = 500;
        return;
    }
    std::cout << "no err\n";
    if (!ok)
    {
        std::cout << "user add start\n";
        emit add_user(email, user, fullName, passw, add, phone, &hasError);
        std::cout << "user add end\n";
    }

    if (ok == 1)
    {
        std::cout << "err wrong user or email\n";
        response.set_content("bad username or bad email","application/json");
        response.status = 400;
        return;
    }

    if (hasError)
    {
        std::cout << "err from user add\n";
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
    std::cout << "getS section\n";
    int id = auId.toInt();

    bool ok, hasError;
    QMap<QString,QString> data;
    std::cout << "get start\n";
    emit get_self(id, &data, &ok, &hasError);
    std::cout << "get end\n";
    if (hasError)
    {
        std::cout << "get err\n";
        response.status = 500;
        return;
    }

    if (!ok)
    {
        std::cout << "not found\n";
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
    std::cout << "getO section\n";
    int id = auId.toInt();

    bool ok, hasError;
    QMap<QString,QString> data;
    std::cout << "get start\n";
    emit get_other(id, &data, &ok, &hasError);
    std::cout << "get end\n";
    if (hasError)
    {
        std::cout << "get err\n";
        response.status = 500;
        return;
    }

    if (!ok)
    {
        std::cout << "not found\n";
        response.status = 404;
        return;
    }

    QString body = R"(","user":")" + data["user"]
                   + R"(","fullName":")" + data["fullName"]
                   + R"(","reg":")" + data["reg"]
                   + R"(","last":")" + data["last"];


    response.set_content(body.toStdString(),"application/json");

    response.status = 200;
}
