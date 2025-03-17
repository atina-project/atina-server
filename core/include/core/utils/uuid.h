#ifndef __ATINA_SERVER_CORE_UTILS_UUID_H__
#define __ATINA_SERVER_CORE_UTILS_UUID_H__

#include<string>

namespace atina::server::core::utils {

    class uuid {

        public:
            static bool compare(const std::string& __c_s_lhs, const std::string& __c_s_rhs);
            static std::string generate();

    }; // class uuid

} // namespace atina::server::core::utils

#endif // __ATINA_SERVER_CORE_UTILS_UUID_H__
