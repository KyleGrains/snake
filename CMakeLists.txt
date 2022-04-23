cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(FetchContent)

FetchContent_Declare(_project_options    
                     URL https://github.com/cpp-best-practices/project_options/archive/refs/tags/v0.17.0.zip)    
FetchContent_MakeAvailable(_project_options)    
include(${_project_options_SOURCE_DIR}/Index.cmake)

project(snake VERSION 1.0)

set(ENABLE_CLANG_TIDY OFF)
set(ENABLE_CPPCHECK OFF)
set(ENABLE_SANITIZER_ADDRESS OFF)

if(STATIC_ANALYZERS)
  set(ENABLE_CLANG_TIDY "ENABLE_CLANG_TIDY")
  set(ENABLE_CPPCHECK "ENABLE_CPPCHECK")
endif()

project_options(
      ${ENABLE_CPPCHECK}
      ${ENABLE_CLANG_TIDY}
      ${ENABLE_CONAN})

find_package(Threads REQUIRED)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(snake src/main.cpp src/screen.cpp src/snake.cpp)

target_include_directories(snake PUBLIC include/)

target_link_libraries(snake ${CONAN_LIBS} Threads::Threads ncurses project_options)
