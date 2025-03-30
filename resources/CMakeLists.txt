project(atina-server-resources)

set(ATINA_SERVER_RESOURCES_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/include CACHE INTERNAL ${CMAKE_CURRENT_BINARY_DIR}/include)

message(STATUS "Generating server resources/resources.h & resources.cpp...")
execute_process(COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/gen_resources_header_src.py" "${ATINA_SERVER_RESOURCES_INCLUDE_DIR}/resources" "${CMAKE_CURRENT_BINARY_DIR}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    ERROR_VARIABLE _ATINA_SERVER_RESOURCES_GEN_ERROR
)
if(_ATINA_SERVER_RESOURCES_GEN_ERROR)
    message(FATAL_ERROR "Failed when trying to generate resources lib source.\n${_ATINA_SERVER_RESOURCES_GEN_ERROR}")
endif()
add_library(${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/resources.cpp
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${ATINA_SERVER_RESOURCES_INCLUDE_DIR}
)
