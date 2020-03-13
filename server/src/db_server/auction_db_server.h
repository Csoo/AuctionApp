//
// Created by petras on 2020. 03. 13..
//

#ifndef AUCTION_SERVER_AUCTION_DB_SERVER_H
#define AUCTION_SERVER_AUCTION_DB_SERVER_H

#include <httplib.h>

using namespace httplib;

class Auction_db_server {
public:
    void temp(const Request &request, Response &response);
};


#endif //AUCTION_SERVER_AUCTION_DB_SERVER_H
