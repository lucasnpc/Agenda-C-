cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_definitions(-std=c++17)

project(AgendaProva)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} src)

file(GLOB SOURCES "src/*.cpp")
add_executable(AgendaProva ${SOURCES})

target_link_libraries(AgendaProva ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} pthread)