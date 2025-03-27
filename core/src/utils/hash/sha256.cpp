#include"core/utils/hash/sha256.h"

#include<iomanip>
#include<openssl/evp.h>
#include<sstream>

using namespace atina::server::core::utils::hash;

std::string sha256::hash(const std::string& __c_s_str){
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx)
    {
        return "";
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    bool ret = EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
    ret &= EVP_DigestUpdate(ctx, __c_s_str.data(), __c_s_str.size());
    ret &= EVP_DigestFinal_ex(ctx, hash, &len);
    EVP_MD_CTX_free(ctx);
    if (!ret)
    {
        return "";
    }

    std::ostringstream oss;
    for (int i = 0 ; i < len ; i++)
    {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return oss.str();
}
