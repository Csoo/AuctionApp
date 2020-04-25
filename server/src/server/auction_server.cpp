//
// Created by petras on 2020. 03. 13..
//

#include "auction_server.h"
#include <iostream>

Auction_server::Auction_server(const std::string &ip, int port) {
    Server server;

    server.Get(R"(/login)",[this](const Request& req, Response& res) {db.login(req,res);});
    server.Get(R"(/auction/(\d+))",[this](const Request& req, Response& res) {db.auction(req,res);});
    server.Get(R"(/user/self/(\d+))",[this](const Request& req, Response& res) {db.getSelf(req,res);});
    server.Get(R"(/user/(\d+))",[this](const Request& req, Response& res) {db.getOther(req,res);});
    server.Get(R"(/shutDown)", [&](const Request& req, Response& res) {for (const auto &h: req.headers) {if (h.first == "pet_server" && h. second == "petras") { std::cout << "Good bye MFs!\n"; db.deleteLater();server.stop();}}});

    server.Post(R"(/reg)",[this](const Request& req, Response& res) {db.userReg(req,res);});
    server.Post(R"(/search)",[this](const Request& req, Response& res) {db.search(req,res);});

    /*server.Put(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});
    server.Delete(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});*/

    std::cout << "Server listen on http://" << ip << ":" << port << std::endl;
    server.listen(ip.c_str(),port);
}
