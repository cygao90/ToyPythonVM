cmake_minimum_required(VERSION 3.16)
Project(ToyPythonVM)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory("${PROJECT_SOURCE_DIR}/src" SOURCE)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

add_executable(ToyPythonVM main.cpp ${SOURCE})