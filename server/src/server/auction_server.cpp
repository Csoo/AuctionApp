//
// Created by petras on 2020. 03. 13..
//

#include "auction_server.h"
#include <QDebug>

Auction_server::Auction_server(const std::string &ip, int port) {
    server.Get(R"(/login)",[this](const Request& req, Response& res) {db.login(req,res);});
    server.Get(R"(/auction/(\d+))",[this](const Request& req, Response& res) {db.auction(req,res);});
    server.Get(R"(/user/self/(\d+))",[this](const Request& req, Response& res) {db.getSelf(req,res);});
    server.Get(R"(/user/(\d+))",[this](const Request& req, Response& res) {db.getOther(req,res);});
    server.Get(R"(/shutDown)", [this](const Request& req, Response& res) {if (res.body == "pet_server/petras") { qWarning() << "Good bye MFs!";server.stop();}});

    server.Post(R"(/reg)",[this](const Request& req, Response& res) {db.userReg(req,res);});
    server.Post(R"(/search)",[this](const Request& req, Response& res) {db.search(req,res);});

    /*server.Put(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});
    server.Delete(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});*/

    std::cout << "Server listen on http://" << ip << ":" << port << std::endl;
    server.listen(ip.c_str(),port);
}