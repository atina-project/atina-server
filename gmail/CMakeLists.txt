set(DATA_DIR ${ATINA_SERVER_INSTALL_DATA_DIR})
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/gmail.cfg.in
    ${CMAKE_CURRENT_BINARY_DIR}/gmail.cfg
    @ONLY
)
install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/gmail.py
    ${CMAKE_CURRENT_BINARY_DIR}/gmail.cfg
    ${CMAKE_CURRENT_SOURCE_DIR}/send_email.sh
    DESTINATION ${ATINA_SERVER_INSTALL_SCRIPT_DIR}
)
