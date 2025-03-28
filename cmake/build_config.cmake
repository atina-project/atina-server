execute_process(
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%h
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} symbolic-ref --short -q HEAD
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
string(TIMESTAMP BUILD_TIME %Y.%m.%d)
if(${ATINA_SERVER_USE_BUILTIN_GMAIL})
    set(USE_BUILTIN_GMAIL 1)
else()
    set(USE_BUILTIN_GMAIL 0)
endif()
configure_file(
    ${CMAKE_SOURCE_DIR}/build_config.h.in
    ${CMAKE_SOURCE_DIR}/core/include/core/build_config.h
    @ONLY
)
