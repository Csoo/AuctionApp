INCLUDE(qt_module)
INCLUDE(3rdparty)
INCLUDE(python)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/db_server)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/auction_closer)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/cpp_email)

SET(SOURCES auction_db_server.cpp)

ADD_LIBRARY(auction_db_server ${SOURCES})

TARGET_LINK_LIBRARIES(auction_db_server Qt5::Core Qt5::Sql db_server auction_closer cpp_email ${PYTHON_LIBRARIES})
