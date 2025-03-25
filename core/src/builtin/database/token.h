#ifndef __ATINA_SERVER_CORE_BUILTIN_DATABASE_TOKEN_H__
#define __ATINA_SERVER_CORE_BUILTIN_DATABASE_TOKEN_H__

#include<condition_variable>
#include<cstdint>
#include<filesystem>
#include<memory>
#include<mutex>
#include<string>
#include<thread>

#include"WCDB/WCDBCpp.h"

namespace atina::server::core::builtin::database {

    class token {

        public:
            token(const std::filesystem::path& __c_fp_db_path);
            ~token();

            /**
             * Request a token for uid. If this uid already has a token, an empty string will be returned.
             *
             * ATTENTION: This function doesn't check uid existance.
             */
            std::string add_token(int __i_uid, const std::string& __c_s_ip_addr, const std::string& __c_s_user_agent);
            /**
             * Check given uid & token with database. If valid then refresh token expire time; if expired then remove it immediately.
             */
            bool check_token_if_valid_refresh_expired_remove(int __i_uid, const std::string& __c_s_token);
            /**
             * Remove all expired tokens in database. If failed, operation will be rollbacked.
             */
            bool cleanup_database();
            /**
             * Close & release database manually.
             *
             * ATTENTION: Before calling this function, call `stop_bg_auto_cleanup()` first.
             * WARNING: Always call this function before exiting program!!! Destructing database automatically by `module_container` causes segmentation fault!!!
             */
            void close_database();
            void delete_token(int __i_uid);
            bool has_uid(int __i_uid);
            void start_bg_auto_cleanup();
            void stop_bg_auto_cleanup();

        private:
            std::filesystem::path _fp_db_path;
            std::unique_ptr<WCDB::Database> _p__db;
            std::recursive_mutex _mtx;
            std::mutex _mtx_bg;
            std::thread _t_bg_worker;
            std::condition_variable _cv_bg;
            bool _b_bg_running;

            uint64_t _ui64_token_valid_time_length;
            uint64_t _ui64_auto_cleanup_interval;
            uint64_t _ui64_last_cleanup_time;

            void _bg_auto_cleanup_task();

    }; // class token

} // namespace atina::server::core::builtin::database

#endif // __ATINA_SERVER_CORE_BUILTIN_DATABASE_TOKEN_H__
