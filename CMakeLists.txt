project(Gnuplot_cours)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 11)

find_package(Boost 1.58.0 COMPONENTS filesystem system iostreams REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})



file(GLOB SOURCES
    src/*)

file(GLOB HEADERS
    include/*)


    
add_executable(exemple exemple.cpp)

target_link_libraries(exemple ${SOURCES} ${HEADERS} ${Boost_LIBRARIES})
