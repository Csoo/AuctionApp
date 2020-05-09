INCLUDE(qt_module)

SET(SOURCES auction_closer.cpp)

ADD_LIBRARY(auction_closer ${SOURCES})

TARGET_LINK_LIBRARIES(auction_closer Qt5::Core)