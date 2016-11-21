cmake_minimum_required(VERSION 3.6)

set(SOURCES main.cpp)

add_executable(markdownpoint ${SOURCES})

target_link_libraries(markdownpoint libmarkdownpoint)
