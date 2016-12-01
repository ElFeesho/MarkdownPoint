cmake_minimum_required(VERSION 3.6)

set(CXX_FEATURE_FLAGS cxx_lambdas cxx_range_for cxx_auto_type)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

project("MarkdownPoint" CXX)

add_subdirectory(markdownpoint)
add_subdirectory(app)

target_compile_features(libmarkdownpoint PRIVATE ${CXX_FEATURE_FLAGS})
target_compile_features(markdownpoint PRIVATE ${CXX_FEATURE_FLAGS})