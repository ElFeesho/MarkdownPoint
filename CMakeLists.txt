cmake_minimum_required(VERSION 3.6)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

project("MarkdownPoint" CXX)

add_subdirectory(markdownpoint)
add_subdirectory(app)

target_compile_features(libmarkdownpoint PRIVATE cxx_lambdas)
target_compile_features(markdownpoint PRIVATE cxx_lambdas)