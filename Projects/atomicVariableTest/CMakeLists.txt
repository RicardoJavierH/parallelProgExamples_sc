cmake_minimum_required(VERSION 3.10)
project(atomicVariableTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

add_executable(atomicVariableTest main.cpp)

