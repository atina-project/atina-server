#ifndef __ATINA_SERVER_CORE_BUILTIN_VALIDATION_CODE_H__
#define __ATINA_SERVER_CORE_BUILTIN_VALIDATION_CODE_H__

#include<cstdint>
#include<memory>
#include<mutex>
#include<string>
#include<unordered_map>

#include"core/config.h"

/**
 * Validation code manager is designed to be non-persistent.
 * Unlike token database, user tokens should be stored even if server has been restarted.
 * But there's no need to create a database for validation code. Losing these codes after restart isn't a big deal.
 */

namespace atina::server::core::builtin {

    class validation_code {

        public:
            typedef struct code {
                std::string s_token;
                std::string s_code;
                uint64_t ui64_expire_time;
            } code;

        public:
            validation_code(std::shared_ptr<config> __p__config);
            ~validation_code(){}

            /**
             * Check validation code. If not match or has already been expired, return false.
             * Cases in code will be ignored.
             *
             * ATTENTION: If validation code verified, this code will be deleted since it can only be used once.
             */
            bool check_validation_code(const std::string& __c_s_token, const std::string& __c_s_code);
            /**
             * Request a new validation code. A struct includes token & code will be returned.
             *
             * ATTENTION: Code size is set default as 6, and should be in range 4 ~ 8.
             * ATTENTION: Do not store tokens or codes somewhere else.
             */
            code get_new_validation_code(int __i_size = 6);

        private:
            typedef struct _code {
                std::string s_code;
                uint64_t ui64_expire_time;
            } _code;

        private:
            std::mutex _mtx;
            std::unordered_map<std::string, _code> _codes;

            const int _c_i_validation_code_min_size = 4;
            const int _c_i_validation_code_max_size = 8;

            std::string _s_charpool;
            unsigned int _ui_valid_time_length_ms;

    }; // class validation_code

} // namespace atina::server::core::builtin

#endif // __ATINA_SERVER_CORE_BUILTIN_VALIDATION_CODE_H__
