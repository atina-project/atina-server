#ifndef __ATINA_SERVER_CORE_UTILS_STRING_H__
#define __ATINA_SERVER_CORE_UTILS_STRING_H__

#include<string>

namespace atina::server::core::utils {

    class string {

        public:
            static std::string to_upper(std::string& __r_s_str);
            static std::string to_lower(std::string& __r_s_str);

    }; // class string

} // namespace atina::server::core::utils

#endif // __ATINA_SERVER_CORE_UTILS_STRING_H__
