cmake_minimum_required(VERSION 3.6)

set(SOURCES src/markdownpoint.cpp)

include_directories(include)

add_library(libmarkdownpoint ${SOURCES})

target_include_directories(libmarkdownpoint PUBLIC include)
target_link_libraries(libmarkdownpoint PUBLIC hpdf)
