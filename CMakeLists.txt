cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(atina-server VERSION 0.0.1 LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(ATINA_SERVER_INSTALL_ROOT_DIR "/opt/atina/server")
else()
    set(ATINA_SERVER_INSTALL_ROOT_DIR "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
    add_definitions(-DATINA_SERVER_DEBUG)
endif()
set(ATINA_SERVER_INSTALL_BIN_DIR "${ATINA_SERVER_INSTALL_ROOT_DIR}/bin")
set(ATINA_SERVER_INSTALL_CONFIG_DIR "${ATINA_SERVER_INSTALL_ROOT_DIR}/config")
set(ATINA_SERVER_INSTALL_DATA_DIR "${ATINA_SERVER_INSTALL_ROOT_DIR}/data")
set(ATINA_SERVER_INSTALL_LIB_DIR "${ATINA_SERVER_INSTALL_ROOT_DIR}/lib")
set(ATINA_SERVER_INSTALL_LOG_DIR "${ATINA_SERVER_INSTALL_ROOT_DIR}/log")
set(ATINA_SERVER_INSTALL_SCRIPT_DIR "${ATINA_SERVER_INSTALL_ROOT_DIR}/script")
option(ATINA_SERVER_USE_BUILTIN_GMAIL "Use builtin Gmail script as default email sender" ON)
set(ATINA_OPENSSL_MIN_VER "3.0.0")
set(BUILD_SHARED_LIBS TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Git REQUIRED)
find_package(OpenSSL ${ATINA_OPENSSL_MIN_VER} COMPONENTS Crypto SSL REQUIRED)
find_package(Python3 REQUIRED)

include(cmake/build_config.cmake)

add_subdirectory(third-party)
add_subdirectory(resources)
add_subdirectory(core)
add_subdirectory(server)
add_subdirectory(emails)

if(${ATINA_SERVER_USE_BUILTIN_GMAIL})
    add_subdirectory(gmail)
endif()

if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
    add_subdirectory(test)
endif()
