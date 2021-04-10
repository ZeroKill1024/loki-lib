cmake_minimum_required(VERSION 3.15)
project(Loki)


OPTION(LOKI_ENABLE_TEST "Enable build test pragrom" OFF)

find_package(Threads REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)
if(LOKI_ENABLE_TEST)
enable_testing()
add_subdirectory(test)
endif()