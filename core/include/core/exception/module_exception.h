#ifndef __ATINA_SERVER_CORE_EXCEPTION_MODULE_EXCEPTION_H__
#define __ATINA_SERVER_CORE_EXCEPTION_MODULE_EXCEPTION_H__

#include"core/exception/basic_exception.h"

namespace atina::server::core::exception {

    ATINA_SERVER_CORE_ADD_NEW_EXCEPTION(module_exception)

    typedef enum module_errcode {
        MODULE_NOT_INITED = 1,
    } module_errcode;

} // namespace atina::server::core::exception

#endif // __ATINA_SERVER_CORE_EXCEPTION_MODULE_EXCEPTION_H__
