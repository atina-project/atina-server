#include"core/utils/encrypt/rsa.h"

#include<openssl/evp.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>

using namespace atina::server::core::utils::encrypt;

std::string rsa::decrypt(const std::vector<uint8_t> __c_vui8_data, const std::string& __c_s_prikey){
    BIO* bio = BIO_new_mem_buf(__c_s_prikey.c_str(), -1);
    if (!bio)
    {
        return {};
    }
    EVP_PKEY* pkey = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    if (!ctx || EVP_PKEY_decrypt_init(ctx) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        return {};
    }

    size_t outlen = 0;
    if (EVP_PKEY_decrypt(ctx, nullptr, &outlen, __c_vui8_data.data(), __c_vui8_data.size()) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        return "";
    }
    std::vector<uint8_t> decrypted(outlen);
    if (EVP_PKEY_decrypt(ctx, decrypted.data(), &outlen, __c_vui8_data.data(), __c_vui8_data.size()) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        return "";
    }

    EVP_PKEY_CTX_free(ctx);
    return std::string(decrypted.begin(), decrypted.begin() + outlen);
}

std::vector<uint8_t> rsa::encrypt(const std::string& __c_s_data, const std::string& __c_s_pubkey){
    BIO* bio = BIO_new_mem_buf(__c_s_pubkey.c_str(), -1);
    if (!bio)
    {
        return {};
    }
    EVP_PKEY* pkey = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    if (!ctx || EVP_PKEY_encrypt_init(ctx) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        return {};
    }

    size_t outlen = 0;
    if (EVP_PKEY_encrypt(ctx, nullptr, &outlen, (const unsigned char*)__c_s_data.data(), __c_s_data.size()) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        return {};
    }
    std::vector<uint8_t> encrypted(outlen);
    if (EVP_PKEY_encrypt(ctx, encrypted.data(), &outlen, (const unsigned char*)__c_s_data.data(), __c_s_data.size()) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        return {};
    }

    EVP_PKEY_CTX_free(ctx);
    encrypted.resize(outlen);
    return encrypted;
}

int rsa::generate(std::string& __o_s_pubkey, std::string& __o_s_prikey, int __i_keygen_bits){
    EVP_PKEY* pkey = nullptr;
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    if (!ctx || EVP_PKEY_keygen_init(ctx) <= 0 || EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, __i_keygen_bits) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        return 1;
    }
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        return 1;
    }
    EVP_PKEY_CTX_free(ctx);

    BIO* bio_pubkey = BIO_new(BIO_s_mem());
    BIO* bio_prikey = BIO_new(BIO_s_mem());
    if (!bio_pubkey || !bio_prikey ||
        PEM_write_bio_PUBKEY(bio_pubkey, pkey) <= 0 ||
        PEM_write_bio_PrivateKey(bio_prikey, pkey, nullptr, nullptr, 0, nullptr, nullptr) <= 0 )
    {
        EVP_PKEY_free(pkey);
        BIO_free(bio_pubkey);
        BIO_free(bio_prikey);
        return 2;
    }

    char* pubkey_data = nullptr;
    char* prikey_data = nullptr;
    long pubkey_data_len = BIO_get_mem_data(bio_pubkey, &pubkey_data);
    long prikey_data_len = BIO_get_mem_data(bio_prikey, &prikey_data);
    __o_s_pubkey = std::string(pubkey_data, pubkey_data_len);
    __o_s_prikey = std::string(prikey_data, prikey_data_len);

    EVP_PKEY_free(pkey);
    BIO_free(bio_pubkey);
    BIO_free(bio_prikey);

    return 0;
}
