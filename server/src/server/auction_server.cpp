//
// Created by petras on 2020. 03. 13..
//

#include "auction_server.h"

Auction_server::Auction_server(const std::string &ip, int port) {
    server.Get(R"(/login)",[this](const Request& req, Response& res) {db.login(req,res);});
    server.Get(R"(/auction/(\d+))",[this](const Request& req, Response& res) {db.auction(req,res);});
    server.Get(R"(/user)",[this](const Request& req, Response& res) {db.getSelf(req,res);});
    server.Get(R"(/user/(\d+))",[this](const Request& req, Response& res) {db.getOther(req,res);});

    server.Post(R"(/user)",[this](const Request& req, Response& res) {db.userReg(req,res);});

    /*server.Put(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});
    server.Delete(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});*/

    std::cout << "Server listen on http://" << ip << ":" << port << std::endl;
    server.listen(ip.c_str(),port);
}
