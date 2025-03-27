#include"core/utils/hash/argon2.h"

#include<argon2.h>
#include<cstdint>
#include<iomanip>
#include<sstream>
#include<vector>

using namespace atina::server::core::utils::hash;

std::string argon2::hash(const std::string& __c_s_pswd, const std::string& __c_s_salt, int __i_iterations, int __i_mem_usage, int __i_threads, int __i_hash_len){
    std::vector<uint8_t> hash(__i_hash_len);
    int res = argon2_hash(
        __i_iterations, __i_mem_usage, __i_threads,
        __c_s_pswd.c_str(), __c_s_pswd.size(),
        __c_s_salt.c_str(), __c_s_salt.size(),
        hash.data(), __i_hash_len, nullptr, 0,
        Argon2_id, ARGON2_VERSION_NUMBER
    );
    if (res != ARGON2_OK)
    {
        return "";
    }
    std::ostringstream oss;
    for (const auto it : hash)
    {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)it;
    }
    return oss.str();
}
