#ifndef __ATINA_SERVER_CORE_UTILS_HASH_ARGON2_H__
#define __ATINA_SERVER_CORE_UTILS_HASH_ARGON2_H__

#include<string>

namespace atina::server::core::utils::hash {

    class argon2 {

        public:
            static std::string hash(const std::string& __c_s_pswd, const std::string& __c_s_salt,
                int __i_iterations = 3,
                int __i_mem_usage = 1 << 12,
                int __i_threads = 1,
                int __i_hash_len = 32
            );

    }; // class argon2

} // namespace atina::server::core::utils::hash

#endif // __ATINA_SERVER_CORE_UTILS_HASH_ARGON2_H__
