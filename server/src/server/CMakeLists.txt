INCLUDE(qt_module)
INCLUDE(3rdparty)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/db_server)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/manager_server)

SET (SOURCES auction_server.cpp)

ADD_LIBRARY(auction_server ${SOURCES})

TARGET_LINK_LIBRARIES(auction_server Qt5::Core db_server)
