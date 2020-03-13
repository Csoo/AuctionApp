INCLUDE(qt_module)
INCLUDE(3rdparty)

SET(SOURCES auction_db_server.cpp)

ADD_LIBRARY(auction_db_server ${SOURCES})

TARGET_LINK_LIBRARIES(auction_db_server Qt5::Core)
