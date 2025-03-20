cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(atina-server VERSION 0.0.1 LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(ATINA_SERVER_INSTALL_DIR "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(ATINA_OPENSSL_MIN_VER "3.0.0")
set(BUILD_SHARED_LIBS TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL ${ATINA_OPENSSL_MIN_VER} COMPONENTS Crypto SSL REQUIRED)

add_subdirectory(third-party)
add_subdirectory(core)

if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
    add_subdirectory(test)
endif()
