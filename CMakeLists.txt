cmake_minimum_required(VERSION 3.8)
project(MTVRPTWSC)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Route.cpp Route.h Param.h Customer.cpp Customer.h TimeWindow.cpp TimeWindow.h Car.cpp Car.h Scenario.cpp Scenario.h)
add_executable(MTVRPTWSC ${SOURCE_FILES})