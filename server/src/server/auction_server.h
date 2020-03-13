//
// Created by petras on 2020. 03. 13..
//

#ifndef AUCTIONAPP_SERVER_H
#define AUCTIONAPP_SERVER_H

#include <iostream>
#include <httplib.h>
#include <auction_db_server.h>

using namespace httplib;

class Auction_server {
public:
        Auction_server(const std::string &ip, int port);
private:
    Server server;
    Auction_db_server db;
};


#endif //AUCTIONAPP_SERVER_H
