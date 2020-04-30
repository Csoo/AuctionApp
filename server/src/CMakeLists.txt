ADD_SUBDIRECTORY(server)
INCLUDE_DIRECTORIES(server)

ADD_SUBDIRECTORY(manager_server)
INCLUDE_DIRECTORIES(manager_server)

ADD_SUBDIRECTORY(db_server)
INCLUDE_DIRECTORIES(db_server)

ADD_SUBDIRECTORY(cpp_email)
INCLUDE_DIRECTORIES(cpp_email)

INCLUDE(3rdparty)

ADD_EXECUTABLE(auctionapp main.cpp)

TARGET_LINK_LIBRARIES(auctionapp auction_server auction_db_server pthread)