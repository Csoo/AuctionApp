//
// Created by petras on 2020. 03. 13..
//

#pragma once

#include <httplib.h>
#include <QString>
#include <QMap>

#include <db_server.h>

using namespace httplib;

class Auction_db_server {
public:
    void login(const Request &request, Response &response);

    void temp(const Request &request, Response &response);

private:
    db_server db;
};
