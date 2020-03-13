//
// Created by petras on 2020. 03. 13..
//

#include "auction_server.h"

Auction_server::Auction_server(const std::string &ip, int port) {
    server.Get(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});
    server.Post(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});
    server.Put(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});
    server.Delete(R"()",[this](const Request& req, Response& res) {db.temp(req,res);});

    std::cout << "Server listen on http://" << ip << ":" << port << std::endl;
    server.listen(ip.c_str(),port);
}
