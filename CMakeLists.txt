cmake_minimum_required(VERSION 2.6)

project(track_velo)

add_definitions(-std=c++11)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/usr/local/include/eigen3)
link_directories(${PROJECT_SOURCE_DIR}/include)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Ofast -Wfatal-errors -D_MWAITXINTRIN_H_INCLUDED")


file(GLOB My_Source_Files ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB My_Test_Files   ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(track_velo ${My_Source_Files} ${My_Test_Files})

add_definitions(-O2 -pthread)

