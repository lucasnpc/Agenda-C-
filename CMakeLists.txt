cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

project(AgendaProva)

file(GLOB SOURCES "src/*.cpp")
add_executable(AgendaProva ${SOURCES})