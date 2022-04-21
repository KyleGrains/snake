cmake_minimum_required(VERSION 3.1)

project(snake VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(snake main.cpp screen.cpp snake.cpp)

target_link_libraries(snake Threads::Threads ${CONAN_LIBS})
