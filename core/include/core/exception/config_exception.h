#ifndef __ATINA_SERVER_CORE_EXCEPTION_CONFIG_EXCEPTION_H__
#define __ATINA_SERVER_CORE_EXCEPTION_CONFIG_EXCEPTION_H__

#include"core/exception/basic_exception.h"

namespace atina::server::core::exception {

    ATINA_SERVER_CORE_ADD_NEW_EXCEPTION(config_exception)

    typedef enum config_errcode {
        CFG_FOLDER_IS_NOT_DIR = 1,
        CFG_CANNOT_OPEN = 2
    } config_errcode;

} // namespace atina::server::core::exception

#endif // __ATINA_SERVER_CORE_EXCEPTION_CONFIG_EXCEPTION_H__
