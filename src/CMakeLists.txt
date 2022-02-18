cmake_minimum_required(VERSION 3.7)
project(mooveit_project CXX)
SET(CMAKE_CXX_FLAGS "-std=c++17")

ADD_SUBDIRECTORY(curlcpp)
INCLUDE_DIRECTORIES(curlcpp/include
                    json
                    include)
add_executable(mooveit_challenge main.cpp)
target_link_libraries(mooveit_challenge curlcpp)

