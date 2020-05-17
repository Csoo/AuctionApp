//
// Created by petras on 2020. 03. 13..
//

#include "auction_server.h"
#include <iostream>

Auction_server::Auction_server(const std::string &ip, int port, const std::string &route) {
    Auction_db_server db(QString::fromStdString(route));
    Server server;

    std::cout << "[Auction_server] Log: Start server" << std::endl;

    server.Get(R"(/auction/(\d+))",[&](const Request& req, Response& res) {db.auction(req,res);});
    server.Get(R"(/auction/all)",[&](const Request& req, Response& res) {db.allAuction(req,res);});
    server.Get(R"(/user/self/(\d+))",[&](const Request& req, Response& res) {db.getSelf(req,res);});
    server.Get(R"(/user/(\d+))",[&](const Request& req, Response& res) {db.getOther(req,res);});
    server.Get(R"(/shutDown)", [&](const Request& req, Response& res) {for (const auto &h: req.headers) {if (h.first == "pet_server" && h. second == "petras") { std::cout << "Good bye MFs!\n"; db.deleteLater();server.stop();}}});

    server.Post(R"(/login)",[&](const Request& req, Response& res) {db.login(req,res);});
    server.Post(R"(/reg)",[&](const Request& req, Response& res) {db.userReg(req,res);});
    server.Post(R"(/search)",[&](const Request& req, Response& res) {db.search(req,res);});
    server.Post(R"(/auction)",[&](const Request& req, Response& res) {db.addAuction(req,res);});
    server.Post(R"(/bid)",[&](const Request& req, Response& res) {db.bid(req,res);});
    server.Post(R"(/rate)",[&](const Request& req, Response& res) {db.rate(req,res);});

    /*server.Put(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});
    server.Delete(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});*/

    std::cout << "Server listen on http://" << ip << ":" << port << std::endl;
    server.listen(ip.c_str(),port);
}
