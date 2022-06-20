cmake_minimum_required(VERSION 3.0.2)
project(net)
add_definitions(-std=c++11)

add_compile_options(-std=c++11)
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
add_executable(test01 src/test01.cpp )
add_executable(test02 src/test02.cpp)
add_executable(test03 src/test03.cpp)
