INCLUDE(qt_module)

SET(SOURCES db_server.cpp)

ADD_LIBRARY(db_server ${SOURCES})

TARGET_LINK_LIBRARIES(db_server Qt5::Core Qt5::Sql)
