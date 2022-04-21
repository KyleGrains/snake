cmake_minimum_required(VERSION 3.1)

project(snake VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(snake src/main.cpp src/screen.cpp src/snake.cpp)

target_include_directories(snake PUBLIC include/)

target_link_libraries(snake Threads::Threads ${CONAN_LIBS})
