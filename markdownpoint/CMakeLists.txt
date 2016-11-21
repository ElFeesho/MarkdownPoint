cmake_minimum_required(VERSION 3.6)

set(SOURCES src/markdownpoint.cpp include/markdownpoint.hpp)

add_subdirectory(gtest)

include_directories(${gtest_SOURCE_DIR}/include)

enable_testing()

add_executable(markdown_parse_test test/markdownparse.cpp)
add_test(markdown_parse_test markdown_parse_test)

include_directories(include)

add_library(libmarkdownpoint ${SOURCES})

target_include_directories(libmarkdownpoint PUBLIC include)
target_link_libraries(libmarkdownpoint PUBLIC hpdf)

target_link_libraries(markdown_parse_test gtest gtest_main libmarkdownpoint)
