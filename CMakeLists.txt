cmake_minimum_required(VERSION 3.24)
project(koral LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_EXPORT_COMPILE_COMMANDS)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
                "${CMAKE_BINARY_DIR}/compile_commands.json"
                "${CMAKE_SOURCE_DIR}/compile_commands.json"
        COMMAND_ERROR_IS_FATAL ANY
    )
endif()

find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Library

file(GLOB_RECURSE LIB_SOURCES
    "src/*.cpp"
)
list(FILTER LIB_SOURCES EXCLUDE REGEX "src/main\\.cpp$")

add_library(koral_lib ${LIB_SOURCES})
target_include_directories(koral_lib PUBLIC include)
target_link_libraries(koral_lib PUBLIC fmt::fmt)

# Executable

add_executable(koral src/main.cpp)
target_link_libraries(koral PRIVATE koral_lib)

# Unit tests

enable_testing()
file(GLOB_RECURSE TESTS "tests/*.cpp")

add_executable(unit_tests ${TESTS})
target_include_directories(unit_tests PRIVATE include tests)
target_link_libraries(unit_tests PRIVATE
    koral_lib
    GTest::gtest
    GTest::gtest_main
    fmt::fmt
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
