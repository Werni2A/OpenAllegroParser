
cmake_minimum_required(VERSION 2.8.12)

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

# Add Boost dependency
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Add libzippp dependency
find_package(libzippp CONFIG REQUIRED)

set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/src/DataStream.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/LayerStuff.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Pad.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser.cpp
)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/src/DataStream.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/General.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/LayerStuff.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Pad.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/PadFile.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser.hpp
)

# Create executable file from sources
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
                           ${Boost_INCLUDE_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
                      ${Boost_LIBRARIES}
                      libzip::zip
                      libzippp::libzippp
)

# add_library( ${CMAKE_PROJECT_NAME} INTERFACE )

# target_include_directories( ${CMAKE_PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )