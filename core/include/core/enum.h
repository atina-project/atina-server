#ifndef __ATINA_SERVER_CORE_ENUM_H__
#define __ATINA_SERVER_CORE_ENUM_H__

#include<string>

namespace atina::server::core {

    typedef enum lang {
        en,
        zhCN
    } lang;

    typedef enum user_type {
        unknown,
        admin,
        normal,
        blocked
    } user_type;

    std::string to_string(lang __lang);
    std::string to_string(user_type __type);

} // namespace atina::server::core

#endif // __ATINA_SERVER_CORE_ENUM_H__
