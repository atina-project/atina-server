#ifndef __ATINA_SERVER_CORE_UTILS_HASH_SHA256_H__
#define __ATINA_SERVER_CORE_UTILS_HASH_SHA256_H__

#include<string>

namespace atina::server::core::utils::hash {

    class sha256 {

        public:
            static std::string hash(const std::string& __c_s_str);

    }; // class sha256

} // namespace atina::server::core::utils::hash

#endif // __ATINA_SERVER_CORE_UTILS_HASH_SHA256_H__
