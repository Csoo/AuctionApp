//
// Created by petras on 2020. 03. 13..
//

#include <QString>
#include <QJsonArray>
#include <iostream>
#include <QJsonDocument>

#include "auction_db_server.h"

//void Auction_db_server::temp(const Request &request, Response &response) {
//
//}

Auction_db_server::Auction_db_server(const QString &route) {
    db = new Db_server("QSQLITE", "Auction", route);
    closes = new QMap<QString,QString>();
    //closer = new Auction_closer(closes);
    db->init();

    QObject::connect(this, &Auction_db_server::check_login, db, &Db_server::check_login_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::check_reg, db, &Db_server::check_reg_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::add_user, db, &Db_server::add_user_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::get_self, db, &Db_server::get_self_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::get_other, db, &Db_server::get_other_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::get_search, db, &Db_server::get_search_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::get_auction, db, &Db_server::get_auction_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::all_auction, db, &Db_server::all_auction_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::get_id, db, &Db_server::get_id_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::add_auction, db, &Db_server::add_auction_slot, Qt::ConnectionType::BlockingQueuedConnection);

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

    emit check_login(user,passw, &ok, &hasError);

    if (hasError)
    {
        std::cout << "error\n";
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

    response.status = 200;
}

void Auction_db_server::userReg(const Request &request, Response &response) {
    response.headers = request.headers;

    if (request.headers.find("Content-Type") == request.headers.end())
    {
        response.status = 400;
        return;
    }

    QString email, user, fullName, passw, add, phone;

    QByteArray bodyStr = QString::fromStdString(request.body).toUtf8();
    QJsonDocument bodyJson = QJsonDocument::fromJson(bodyStr);

    QVariantMap body = bodyJson.toVariant().toMap();

    try
    {
        email = body.value("email").toString();
        user = body.value("user").toString();
        fullName = body.value("fullName").toString();
        passw = body.value("password").toString();
        add = body.value("address").toString();
    }
    catch (...)
    {
        response.status = 400;
        return;
    }

    std::cout << "data ok\n";

    phone = body.value("phone").toString();

    std::cout << "phone ok\n";
    bool ok, hasError;

    emit check_reg(email, user, &ok, &hasError);

    if (hasError)
    {
        response.status = 500;
        return;
    }
    std::cout << "no error\n";
    if (!ok)
    {
        std::cout << "user add start\n";
        std::cout << email.toStdString() << std::endl << user.toStdString() << std::endl << fullName.toStdString() << std::endl << passw.toStdString() << std::endl << add.toStdString() << std::endl << phone.toStdString() << std::endl;

        emit add_user(email, user, fullName, passw, add, phone, &hasError);
        std::cout << "user add end\n";
    }

    if (ok)
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

    if (request.headers.find("Content-Type") == request.headers.end())
    {
        response.status = 400;
        return;
    }

    QString text, category;

    QByteArray bodyStr = QString::fromStdString(request.body).toUtf8();
    QJsonDocument bodyJson = QJsonDocument::fromJson(bodyStr), filters, resJSON;

    QVariantMap body = bodyJson.toVariant().toMap();

    try
    {
        text = body.value("text").toString();
        category = body.value("category").toString();
        filters = body.value("filters").toJsonDocument();

    }
    catch (...)
    {
        response.status = 400;
        return;
    }

    bool hasError;

    emit get_search(text, category, filters, &resJSON, &hasError);

    if (hasError)
    {
        response.status = 500;
        return;
    }

    if (resJSON.isEmpty())
    {
        response.status = 404;
        return;
    }

    QString resString(resJSON.toJson());
    response.set_content(resString.toStdString(),"application/json");

    response.status = 200;
}

void Auction_db_server::auction(const Request &request, Response &response) {
    QString auId = QString::fromStdString(request.matches[1].str());

    int id = auId.toInt();

    bool hasError;
    QJsonDocument resJSON;

    emit get_auction(id, &resJSON, &hasError);

    if (hasError)
    {
        response.status = 500;
        return;
    }

    if (resJSON.isEmpty())
    {
        response.status = 404;
        return;
    }

    QString resString(resJSON.toJson());
    response.set_content(resString.toStdString(),"application/json");

    response.status = 200;
}

void Auction_db_server::allAuction(const Request &request, Response &response) {
    bool hasError;
    QJsonDocument resJSON;

    emit all_auction(&resJSON, &hasError);

    if (hasError)
    {
        response.status = 500;
        return;
    }

    if (resJSON.isEmpty())
    {
        response.status = 404;
        return;
    }

    QString resString(resJSON.toJson());
    response.set_content(resString.toStdString(),"application/json");

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
                + R"(","reg":")" + data["reg"] + "\"\n}";


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

    QString body = R"({"user":")" + data["user"]
                   + R"(","fullName":")" + data["fullName"]
                   + R"(","reg":")" + data["reg"]
                   + R"(","last":")" + data["last"] + "\"\n}";


    response.set_content(body.toStdString(),"application/json");

    response.status = 200;
}

void Auction_db_server::addAuction(const Request &request, Response &response) {
    if (request.headers.find("Content-Type") == request.headers.end())
    {
        response.status = 400;
        return;
    }

    QByteArray bodyStr = QString::fromStdString(request.body).toUtf8();
    QJsonDocument bodyJson = QJsonDocument::fromJson(bodyStr), filters, resJSON;

    QVariantMap body = bodyJson.toVariant().toMap();

    QMap<QString,QString> p;
    QString tag;

    try
    {
        p["user"] = body.value("user_id").toString();
        p["title"] = body.value("title").toString();
        p["description"] = body.value("description_text").toString();
        p["color"] = body.value("color").toString();
        p["cp"] = body.value("current_price").toString();
        p["mins"] = body.value("min_step").toString();
        p["categ"] = body.value("category").toString();
        p["condition"] = body.value("condition_id").toString();
        tag = body.value("tags").toString();
        p["ed"] = body.value("end_date").toString();
    }
    catch (...)
    {
        response.body = "false";
        response.status = 400;
        return;
    }

    QStringList tags;

    tag = tag.mid(1,tag.length()-2);
    tags = tag.split(',');

    for (auto &t: tags) {
        t = t.mid(1,t.length()-2);
    }

    bool hasError;

    emit add_auction(p, tags, &hasError);

    if (hasError)
    {
        response.status = 500;
        return;
    }

    QString id;

    emit get_id(p["user"], &id, &hasError);

    if (hasError)
    {
        response.status = 500;
        return;
    }

    closes->insert(id, p["ed"]);

    response.set_content(id.toStdString(),"application/json");
    response.status = 200;
}

void Auction_db_server::bid(const Request &request, Response &response) {
    if (request.headers.find("Content-Type") == request.headers.end())
    {
        response.status = 400;
        return;
    }

    QByteArray bodyStr = QString::fromStdString(request.body).toUtf8();
    QJsonDocument bodyJson = QJsonDocument::fromJson(bodyStr), filters, resJSON;

    QVariantMap body = bodyJson.toVariant().toMap();

    QString auction, licit_use;
    int current_price, bid;

    try
    {
        auction = body.value("auction_id").toString();
        licit_use = body.value("licit_user_id").toString();
        current_price = body.value("current_price").toInt();
        bid = body.value("bid").toInt();
    }
    catch (...)
    {
        response.status = 400;
        return;
    }

    //check auction close
    if (!closes->contains(auction))
    {
        response.status = 404;
        return;
    }

    bool hasError;

    //check bid
    emit ;

    if (hasError)
    {
        response.status = 500;
        return;
    }

    //set bid
    emit ;

    if (hasError)
    {
        response.status = 500;
        return;
    }

    response.set_content("","application/json");
    response.status = 200;
}
