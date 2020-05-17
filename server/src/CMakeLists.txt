ADD_SUBDIRECTORY(server)
INCLUDE_DIRECTORIES(server)

ADD_SUBDIRECTORY(manager_server)
INCLUDE_DIRECTORIES(manager_server)

ADD_SUBDIRECTORY(db_server)
INCLUDE_DIRECTORIES(db_server)

ADD_SUBDIRECTORY(cpp_email)
INCLUDE_DIRECTORIES(cpp_email)

ADD_SUBDIRECTORY(auction_closer)
INCLUDE_DIRECTORIES(auction_closer)

INCLUDE(3rdparty)
INCLUDE(python)

ADD_EXECUTABLE(auctionapp main.cpp)

TARGET_LINK_LIBRARIES(auctionapp auction_server auction_db_server pthread cpp_email auction_closer ${PYTHON_LIBRARIES})