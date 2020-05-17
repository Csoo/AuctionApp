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
    closer = new Auction_closer(closes);
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
    QObject::connect(this, &Auction_db_server::server_start, closer, &Auction_closer::server_start_slot, Qt::ConnectionType::QueuedConnection);
    QObject::connect(this, &Auction_db_server::check_bid, db, &Db_server::check_bid_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::set_bid, db, &Db_server::set_bid_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(closer, &Auction_closer::add_rating, db, &Db_server::add_rating_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::set_rating, db, &Db_server::set_rating_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(closer, &Auction_closer::read_closes, db, &Db_server::read_closes_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(closer, &Auction_closer::get_close_data, db, &Db_server::get_close_data_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(closer, &Auction_closer::get_email, db, &Db_server::get_email_slot, Qt::ConnectionType::BlockingQueuedConnection);
    QObject::connect(this, &Auction_db_server::get_rate, db, &Db_server::get_rate_slot, Qt::ConnectionType::BlockingQueuedConnection);

    db->start();
    closer->start();

    emit server_start();

    std::cout << "[Auction_db_server] Log: Start server & Start Db_server & Start Auction_closer" << std::endl;
}

void Auction_db_server::login(const Request &request, Response &response) {
    std::cout << "[Auction_db_server] Log: Get login request" << std::endl;
    response.headers = request.headers;

    if (request.headers.find("Content-Type") == request.headers.end())
    {
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Request body Content-Type - OK" << std::endl;

    QString user, passw;

    QByteArray bodyStr = QString::fromStdString(request.body).toUtf8();
    QJsonDocument bodyJson = QJsonDocument::fromJson(bodyStr);

    QVariantMap body = bodyJson.toVariant().toMap();

    try
    {
        user = body.value("user").toString();
        passw = body.value("password").toString();
    }
    catch (...)
    {
        std::cout << "[Auction_db_server] Error: Too few argument for request" << std::endl;
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Login parameters dumped" << std::endl;

    bool ok, hasError;
    int id;

    emit check_login(user, passw, &id, &ok, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    if (ok)
    {
        std::cout << "[Auction_db_server] Log: Login success" << std::endl;
        response.set_content(QString::number(id).toStdString(),"application/json");
    }
    else
    {
        std::cout << "[Auction_db_server] Log: Login failed" << std::endl;
        response.set_content("false","application/json");
    }

    response.status = 200;
}

void Auction_db_server::userReg(const Request &request, Response &response) {
    std::cout << "[Auction_db_server] Log: Get registration request" << std::endl;
    response.headers = request.headers;

    if (request.headers.find("Content-Type") == request.headers.end())
    {
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Request body Content-Type - OK" << std::endl;

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
        std::cout << "[Auction_db_server] Error: Too few argument for request" << std::endl;
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Registration parameters dumped" << std::endl;

    phone = body.value("phone").toString();

    std::cout << "[Auction_db_server] Log: Phone got" << std::endl;
    bool ok, hasError;

    std::cout << "[Auction_db_server] Log: Request Db_server for registration check" << std::endl;
    emit check_reg(email, user, &ok, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    if (!ok)
    {
        std::cout << "[Auction_db_server] Log: Request Db_server for add user" << std::endl;
        std::cout << email.toStdString() << std::endl << user.toStdString() << std::endl << fullName.toStdString() << std::endl << passw.toStdString() << std::endl << add.toStdString() << std::endl << phone.toStdString() << std::endl;

        emit add_user(email, user, fullName, passw, add, phone, &hasError);

        Email notification(email.toStdString(), "Registration notification", "Dear " + fullName.toStdString() + ",\nRegistration of " +
                            user.toStdString() + " succeeded");
        notification.prepare();
        notification.send();
        std::cout << "[Auction_db_server] Log: Email to just registered user sent" << std::endl;
        //	Email* email = new Email("stecsabi@gmail.com", "TEszt fejlec", "asdasdasdasdasdsasadasddasasdasdasdasdasd");
        //	email->prepare();
        //	email->send();
    }

    if (ok)
    {
        std::cout << "[Auction_db_server] Log: Request Db_server for add user failed - bad username or email" << std::endl;
        response.set_content("bad username or bad email","application/json");
        response.status = 400;
        return;
    }

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    response.status = 200;
}

void Auction_db_server::search(const Request &request, Response &response) {
    std::cout << "[Auction_db_server] Log: Get search request" << std::endl;
    response.headers = request.headers;

    if (request.headers.find("Content-Type") == request.headers.end())
    {
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Request body Content-Type - OK" << std::endl;

    QString text, category, tag;

    QByteArray bodyStr = QString::fromStdString(request.body).toUtf8();
    QJsonDocument bodyJson = QJsonDocument::fromJson(bodyStr), filters, resJSON;

    QVariantMap body = bodyJson.toVariant().toMap();

    try
    {
        text = body.value("text").toString();
        category = body.value("category").toString();
        filters = body.value("filters").toJsonDocument();
        tag = body.value("tags").toString();

    }
    catch (...)
    {
        std::cout << "[Auction_db_server] Error: Too few argument for request" << std::endl;
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Search parameters dumped" << std::endl;

    QStringList tags;

    tag = tag.mid(1,tag.length()-2);
    tags = tag.split(',');

    for (auto &t: tags) {
        t = t.mid(1,t.length()-2);
    }

    bool hasError;

    std::cout << "[Auction_db_server] Log: Request Db_server for search auctions" << std::endl;
    emit get_search(text, category, filters, tags, &resJSON, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    if (resJSON.isEmpty())
    {
        std::cout << "[Auction_db_server] Error: resJSON is empty from Db_server" << std::endl;
        response.status = 404;
        return;
    }

    QString resString(resJSON.toJson());
    response.set_content(resString.toStdString(),"application/json");

    response.status = 200;
}

void Auction_db_server::auction(const Request &request, Response &response) {
    std::cout << "[Auction_db_server] Log: Get auction getter request" << std::endl;
    QString auId = QString::fromStdString(request.matches[1].str());

    int id = auId.toInt();

    bool hasError;
    QJsonDocument resJSON;

    std::cout << "[Auction_db_server] Log: Request Db_server for get auction by id" << std::endl;
    emit get_auction(id, &resJSON, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    if (resJSON.isEmpty())
    {
        std::cout << "[Auction_db_server] Error: resJSON is empty from Db_server" << std::endl;
        response.status = 404;
        return;
    }

    QString resString(resJSON.toJson());
    response.set_content(resString.toStdString(),"application/json");

    response.status = 200;
}

void Auction_db_server::allAuction(const Request &request, Response &response) {
    std::cout << "[Auction_db_server] Log: Get request for get all auction" << std::endl;
    bool hasError;
    QJsonDocument resJSON;

    std::cout << "[Auction_db_server] Log: Request Db_server for get all auctions" << std::endl;
    emit all_auction(&resJSON, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    if (resJSON.isEmpty())
    {
        std::cout << "[Auction_db_server] Error: resJSON is empty from Db_server" << std::endl;
        response.status = 404;
        return;
    }

    QString resString(resJSON.toJson());
    response.set_content(resString.toStdString(),"application/json");

    response.status = 200;
}

void Auction_db_server::getSelf(const Request &request, Response &response) {
    std::cout << "[Auction_db_server] Log: Get request for self data" << std::endl;
    QString auId = QString::fromStdString(request.matches[1].str());

    int id = auId.toInt();

    bool ok, hasError;
    QMap<QString,QString> data;
    QString positive, negative;

    std::cout << "[Auction_db_server] Log: Request Db_server for get self data" << std::endl;
    emit get_self(id, &data, &ok, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    if (!ok)
    {
        std::cout << "[Auction_db_server] Error: Self user not found" << std::endl;
        response.status = 404;
        return;
    }

    emit get_rate(QString::number(id), positive, negative, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    QString body = R"({"email":")" + data["email"]
                + R"(","user":")" + data["user"]
                + R"(","fullName":")" + data["fullName"]
                + R"(","address":")" + data["address"]
                + R"(","phone":")" + data["phone"]
                + R"(","reg":")" + data["reg"]
                + R"(","positive":")" + positive
                + R"(","negative":")" + negative
                + "\"\n}";

    std::cout << "[Auction_db_server] Log: Response body dumped" << std::endl;

    response.set_content(body.toStdString(),"application/json");

    response.status = 200;
}

void Auction_db_server::getOther(const Request &request, Response &response) {
    std::cout << "[Auction_db_server] Log: Get request for user data" << std::endl;
    QString auId = QString::fromStdString(request.matches[1].str());

    int id = auId.toInt();

    bool ok, hasError;
    QMap<QString,QString> data;
    QString positive, negative;

    std::cout << "[Auction_db_server] Log: Request Db_server for get user data" << std::endl;
    emit get_other(id, &data, &ok, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    if (!ok)
    {
        std::cout << "[Auction_db_server] Error: User " + QString::number(id).toStdString() + " not found" << std::endl;
        response.status = 404;
        return;
    }

    emit get_rate(data["user"], positive, negative, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    QString body = R"({"user":")" + data["user"]
                   + R"(","fullName":")" + data["fullName"]
                   + R"(","reg":")" + data["reg"]
                   + R"(","last":")" + data["last"]
                   + R"(","positive":")" + positive
                   + R"(","negative":")" + negative
                   + "\"\n}";

    std::cout << "[Auction_db_server] Log: Response body dumped" << std::endl;

    response.set_content(body.toStdString(),"application/json");

    response.status = 200;
}

void Auction_db_server::addAuction(const Request &request, Response &response) {
    std::cout << "[Auction_db_server] Log: Get add request for auction" << std::endl;
    if (request.headers.find("Content-Type") == request.headers.end())
    {
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Request body Content-Type - OK" << std::endl;

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
        std::cout << "[Auction_db_server] Error: Too few argument for request" << std::endl;
        response.body = "false";
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Registration parameters dumped" << std::endl;

    QStringList tags;

    tag = tag.mid(1,tag.length()-2);
    tags = tag.split(',');

    for (auto &t: tags) {
        t = t.mid(1,t.length()-2);
    }

    bool hasError;

    std::cout << "[Auction_db_server] Log: Request Db_server for add auction" << std::endl;
    emit add_auction(p, tags, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    QString id;

    std::cout << "[Auction_db_server] Log: Request Db_server for check added auction" << std::endl;
    emit get_id(p["user"], &id, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    //id, end_date
    closes->insert(id, p["ed"]);

    response.set_content(id.toStdString(),"application/json");
    response.status = 200;
}

void Auction_db_server::bid(const Request &request, Response &response) {
    std::cout << "[Auction_db_server] Log: Get bid request" << std::endl;
    if (request.headers.find("Content-Type") == request.headers.end())
    {
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Request body Content-Type - OK" << std::endl;

    QByteArray bodyStr = QString::fromStdString(request.body).toUtf8();
    QJsonDocument bodyJson = QJsonDocument::fromJson(bodyStr), filters, resJSON;

    QVariantMap body = bodyJson.toVariant().toMap();

    QString auction, licit_user;
    int current_price, bid;

    try
    {
        auction = body.value("auction_id").toString();
        licit_user = body.value("licit_user_id").toString();
        current_price = body.value("current_price").toInt();
        bid = body.value("bid").toInt();
    }
    catch (...)
    {
        std::cout << "[Auction_db_server] Error: Too few argument for request" << std::endl;
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Bid parameters dumped" << std::endl;

    //check auction close
    if (!closes->contains(auction))
    {
        response.status = 404;
        return;
    }

    bool hasError, ok;

    std::cout << "[Auction_db_server] Log: Request Db_server for validate bid" << std::endl;
    emit check_bid(auction, current_price, &ok, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    if (ok)
    {
        std::cout << "[Auction_db_server] Log: Request Db_server for set bid by parameters" << std::endl;
        emit set_bid(auction, licit_user, current_price + bid, &hasError);
    }
    else
    {
        std::cout << "[Auction_db_server] Error: Higher price" << std::endl;
        response.status = 400;
        return;
    }

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    response.set_content(QString::number(current_price + bid).toStdString(),"application/json");
    response.status = 200;
}

void Auction_db_server::rate(const Request &request, Response &response) {
    std::cout << "[Auction_db_server] Log: Get rate request" << std::endl;
    if (request.headers.find("Content-Type") == request.headers.end())
    {
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Request body Content-Type - OK" << std::endl;

    QByteArray bodyStr = QString::fromStdString(request.body).toUtf8();
    QJsonDocument bodyJson = QJsonDocument::fromJson(bodyStr), filters, resJSON;

    QVariantMap body = bodyJson.toVariant().toMap();

    QString ms, from, to, p;

    try
    {
        from = body.value("user_id_from").toString();
        to = body.value("user_id_to").toString();
        p = body.value("positive").toString();
        ms = body.value("message").toString();
    }
    catch (...)
    {
        std::cout << "[Auction_db_server] Error: Too few argument for request" << std::endl;
        response.status = 400;
        return;
    }
    std::cout << "[Auction_db_server] Log: Rating parameters dumped" << std::endl;

    bool hasError;

    emit set_rating(to, from, p, ms, &hasError);

    if (hasError)
    {
        std::cout << "[Auction_db_server] Error: From Db_server" << std::endl;
        response.status = 500;
        return;
    }

    response.set_content(to.toStdString(),"application/json");
    response.status = 200;
}
