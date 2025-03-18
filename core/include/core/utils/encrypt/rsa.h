#ifndef __ATINA_SERVER_CORE_UTILS_ENCRYPT_RSA_H__
#define __ATINA_SERVER_CORE_UTILS_ENCRYPT_RSA_H__

#include<cstdint>
#include<string>
#include<vector>

namespace atina::server::core::utils::encrypt {

    class rsa {

        public:
            static std::string decrypt(const std::vector<uint8_t> __c_vui8_data, const std::string& __c_s_prikey);
            static std::vector<uint8_t> encrypt(const std::string& __c_s_data, const std::string& __c_s_pubkey);
            static int generate(std::string& __o_s_pubkey, std::string& __o_s_prikey, int __i_keygen_bits = 2048);

    }; // class rsa

} // namespace atina::server::core::utils::encrypt

#endif // __ATINA_SERVER_CORE_UTILS_ENCRYPT_RSA_H__
