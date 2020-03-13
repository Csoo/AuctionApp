ADD_SUBDIRECTORY(server)
INCLUDE_DIRECTORIES(server)

ADD_EXECUTABLE(auction_server main.cpp)

TARGET_LINK_LIBRARIES(auction_server server pthread)