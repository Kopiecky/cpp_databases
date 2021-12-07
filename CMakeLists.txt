cmake_minimum_required(VERSION 3.8)
project( dbconn ) 

file(GLOB main
        "src/main.cpp")
file(GLOB database
        "src/database/*.cpp")
file(GLOB client
        "src/client/*.cpp")
file(GLOB server
        "src/server/*.cpp")
file(GLOB sensor
        "src/sensor/*.cpp")
file(GLOB serial
        "src/serial/*.cpp")
file(GLOB argparser
        "src/argparser/*.cpp")

add_executable( dbconn ${main} ${database} ${client} ${server} ${sensor} ${serial} ${argparser})
add_compile_options(-Wall -Wpedantic -Werror)

target_include_directories( dbconn PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src )

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )
find_package(MySQL REQUIRED)

include_directories(${MYSQL_INCLUDE_DIR})
target_link_libraries( dbconn ${MYSQL_LIBRARY} )