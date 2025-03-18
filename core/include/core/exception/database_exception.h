#ifndef __ATINA_SERVER_CORE_EXCEPTION_DATABASE_EXCEPTION_H__
#define __ATINA_SERVER_CORE_EXCEPTION_DATABASE_EXCEPTION_H__

#include"core/exception/basic_exception.h"

namespace atina::server::core::exception {

    ATINA_SERVER_CORE_ADD_NEW_EXCEPTION(database_exception)

    typedef enum database_errcode {
        DB_CANNOT_OPEN = 1,
        DB_CREATION_FAILED = 2,
        DB_TABLE_NOT_EXISTS = 3,
        DB_GET_VALUE_FAILED = 4,
    } database_errcode;

} // namespace atina::server::core::exception

#endif // __ATINA_SERVER_CORE_EXCEPTION_DATABASE_EXCEPTION_H__
