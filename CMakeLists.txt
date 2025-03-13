cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(atina-server VERSION 0.0.1 LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(ATINA_SERVER_INSTALL_DIR "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(BUILD_SHARED_LIBS TRUE)

add_subdirectory(third-party)
