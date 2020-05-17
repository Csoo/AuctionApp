//
// Created by petras on 2020. 03. 13..
//

#pragma once

#include <iostream>
#include <httplib.h>
#include <auction_db_server.h>

using namespace httplib;

class Auction_server {
public:
        Auction_server(const std::string &ip, int port, const std::string &route);
};
