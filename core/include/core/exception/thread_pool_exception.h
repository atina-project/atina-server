#ifndef __ATINA_SERVER_CORE_EXCEPTION_THREAD_POOL_EXCEPTION_H__
#define __ATINA_SERVER_CORE_EXCEPTION_THREAD_POOL_EXCEPTION_H__

#include"core/exception/basic_exception.h"

namespace atina::server::core::exception {

    ATINA_SERVER_CORE_ADD_NEW_EXCEPTION(thread_pool_exception);

    typedef enum thread_pool_errcode {
        THREAD_POOL_NOT_RUNNING = 1,
    } thread_pool_errcode;

} // namespace atina::server::core::exception

#endif // __ATINA_SERVER_CORE_EXCEPTION_THREAD_POOL_EXCEPTION_H__
