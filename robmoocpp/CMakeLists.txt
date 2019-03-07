project(Robmooc_cpp)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 11)

find_package(Boost 1.58.0 COMPONENTS filesystem system iostreams REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})



file(GLOB SOURCES
    ../src/*)

file(GLOB HEADERS
    ../include/*)


    
add_executable(1.13_ex_schuler_imu 1.13_ex_schuler_imu.cpp)
add_executable(1.14_ex_lie_control 1.14_ex_lie_control.cpp)
add_executable(2.01_ex_crank 2.01_ex_crank.cpp)

target_link_libraries(1.13_ex_schuler_imu ${SOURCES} ${HEADERS} ${Boost_LIBRARIES})
target_link_libraries(1.14_ex_lie_control ${SOURCES} ${HEADERS} ${Boost_LIBRARIES})
target_link_libraries(2.01_ex_crank ${SOURCES} ${HEADERS} ${Boost_LIBRARIES})