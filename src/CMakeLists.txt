cmake_minimum_required(VERSION 3.7)
project(mooveit_project CXX)
ADD_SUBDIRECTORY(curlcpp) 

INCLUDE_DIRECTORIES(curlcpp/include
                    json)
add_executable(mooveit_challenge main.cpp)
