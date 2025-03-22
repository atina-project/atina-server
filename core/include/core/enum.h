#ifndef __ATINA_SERVER_CORE_ENUM_H__
#define __ATINA_SERVER_CORE_ENUM_H__

namespace atina::server::core {

    typedef enum user_type {
        unknown,
        admin,
        normal,
        blocked
    } user_type;

} // namespace atina::server::core

#endif // __ATINA_SERVER_CORE_ENUM_H__
