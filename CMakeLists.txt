cmake_minimum_required(VERSION 3.16)
Project(ToyPythonVM)

set(CMAKE_CXX_STANDARD 11)

FILE(GLOB SOURCE "${CMAKE_SOURCE_DIR}/src/*.cpp")

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")

add_executable(ToyPythonVM ${SOURCE} ${INCLUDE_DIRECTORIES})