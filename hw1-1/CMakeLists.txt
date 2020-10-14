cmake_minimum_required(VERSION 3.10)
project(hw1)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hw1 main.cpp)
target_link_libraries(  hw1 ${OpenCV_LIBS}  )