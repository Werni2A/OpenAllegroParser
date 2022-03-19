
cmake_minimum_required(VERSION 3.5)

project(OpenAllegroParser)

if(CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "CMAKE_BUILD_TYPE not defined, 'Debug' will be used")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
endif()

set(LIB_SRC_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/lib/src)
set(LIB_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)
set(CLI_SRC_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/cli/src)
set(CLI_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/cli/include)
set(TEST_SRC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/test/src)
set(TEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test/include)

set(NAME_LIB  OpenAllegroParser)
set(NAME_CLI  OpenAllegroParser-cli)
set(NAME_TEST test)

add_subdirectory(lib)
add_subdirectory(cli)
add_subdirectory(test)