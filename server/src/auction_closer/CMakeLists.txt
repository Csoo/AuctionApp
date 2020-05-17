INCLUDE(qt_module)
INCLUDE(python)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/cpp_email)

SET(SOURCES auction_closer.cpp)

ADD_LIBRARY(auction_closer ${SOURCES})

TARGET_LINK_LIBRARIES(auction_closer Qt5::Core cpp_email ${PYTHON_LIBRARIES})