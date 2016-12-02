cmake_minimum_required(VERSION 3.6)

find_package(Boost 1.62.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(SOURCES main.cpp document.cpp document.hpp)

add_executable(markdownpoint ${SOURCES})

target_link_libraries(markdownpoint libmarkdownpoint hpdf)