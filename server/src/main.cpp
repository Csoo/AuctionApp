//
// Created by petras on 2020. 03. 13..
//

#include <iostream>

#include <auction_server.h>

int main (int argc, char* argv[]) {

    std::cout << "---Welcome in Auctionapp server CLI---" << std::endl << std::endl;

    std::cout << "Please enter the listening ip for the server (to default: 0.0.0.0 type -1)" << std::endl;

    std::string ip;
    std::cin >> ip;

    if (ip == "-1")
    {
        ip = "0.0.0.0";
    }

    std::cout << "Please enter the listening port for the server (to default: 3000 type -1)" << std::endl;

    int port;
    std::cin >> port;

    if (port == -1) {
        port = 3000;
    }

    Auction_server a_server(ip,port);

    return 0;
}