INCLUDE(python)

SET(SOURCES cpp_email.cpp)

ADD_LIBRARY(cpp_email ${SOURCES})

target_link_libraries(cpp_email ${PYTHON_LIBRARIES})
