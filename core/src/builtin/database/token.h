#ifndef __ATINA_SERVER_CORE_BUILTIN_DATABASE_TOKEN_H__
#define __ATINA_SERVER_CORE_BUILTIN_DATABASE_TOKEN_H__

#include<cstdint>
#include<filesystem>
#include<memory>
#include<mutex>
#include<string>

#include"core/task_scheduler.h"
#include"WCDB/WCDBCpp.h"

namespace atina::server::core::builtin::database {

    class token {

        public:
            token(std::shared_ptr<task_scheduler> __p__scheduler);
            ~token();

            /**
             * Request a token for uid. If this uid alsready has a token, an empty string will be returned.
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
             * WARNING: Always call this function before exiting program!!! Destructing database automatically by `module_container` causes segmentation fault!!!
             */
            void close_database();
            void delete_token(int __i_uid);
            bool has_uid(int __i_uid);

        private:
            std::filesystem::path _fp_db_path;
            std::unique_ptr<WCDB::Database> _p__db;
            std::recursive_mutex _mtx;
            std::shared_ptr<task_scheduler> _p__scheduler;
            int _i_bg_task_token;
            uint64_t _ui64_token_valid_time_length_ms;
            uint64_t _ui64_auto_cleanup_interval_min;

    }; // class token

} // namespace atina::server::core::builtin::database

#endif // __ATINA_SERVER_CORE_BUILTIN_DATABASE_TOKEN_H__
