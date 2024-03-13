cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:/MySQL/MySQL Connector C++ 8.3/include)

link_directories(C:/MySQL/MySQL Connector C++ 8.3/lib64)

add_executable(untitled main.cpp)

target_link_libraries(untitled mysqlcppconn)

