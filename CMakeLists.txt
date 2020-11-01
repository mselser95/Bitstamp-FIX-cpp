cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 14)

include_directories(".")
add_executable(test connector/fix/Connector.cpp connector/fix/Connector.h config.h brain.cpp connector/Bitstamp.cpp connector/Bitstamp.h Book.h)
find_library(MY_LIB quickfix library PATHS /home/matias/Desktop/quickfix/lib)
TARGET_LINK_LIBRARIES(test ${MY_LIB})
find_library(CURL_LIB curl library PATHS /usr/include/curlpp)
TARGET_LINK_LIBRARIES(test ${CURL_LIB})


