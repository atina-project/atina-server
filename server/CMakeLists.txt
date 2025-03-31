project(atina-server-server)

set(ATINA_SERVER_SERVER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(_SERVER_SRC_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/localport.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/modules.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
)

add_executable(atina_server
    ${_SERVER_SRC_LIST}
)
target_include_directories(atina_server
    PUBLIC
        ${ATINA_SERVER_CORE_INCLUDE_DIR}
        ${ATINA_SERVER_SERVER_INCLUDE_DIR}
    PRIVATE
        ${HTTPLIB_INCLUDE_DIR}
        ${HYPODERMIC_INCLUDE_DIR}
        ${JSONCPP_INCLUDE_DIR}
)
target_link_libraries(atina_server
    atina-server-core
    httplib::httplib
    jsoncpp_lib
)
