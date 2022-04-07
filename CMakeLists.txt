cmake_minimum_required(VERSION 3.1)

project(snake VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})

add_executable(snake main.cpp screen.cpp snake.cpp)

target_link_libraries(snake ${CURSES_LIBRARIES} Threads::Threads)
