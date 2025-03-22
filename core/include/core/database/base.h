#ifndef __ATINA_SERVER_CORE_DATABASE_BASE_H__
#define __ATINA_SERVER_CORE_DATABASE_BASE_H__

#include<cstdint>
#include<filesystem>
#include<memory>

#include"core/enum.h"
#include"WCDB/WCDBCpp.h"

namespace atina::server::core::database {

    class base {

        public:
            typedef struct user_data {
                const int uid;
                const std::string username;
                const std::string pswd;
                const std::string email;
                const user_type usertype;
                const std::string name;
                const std::string tag;
                const uint64_t reg_time;
                const uint64_t last_login_time;
                user_data(
                    int __i_uid, const std::string& __c_s_username, const std::string& __c_s_pswd,
                    const std::string& __c_s_email, user_type __i_usertype,
                    const std::string& __c_s_name, const std::string& __c_s_tag,
                    uint64_t __ui64_reg_time, uint64_t __ui64_last_login_time
                ) : uid(__i_uid), username(__c_s_username), pswd(__c_s_pswd), email(__c_s_email),
                    usertype(__i_usertype), name(__c_s_name), tag(__c_s_tag),
                    reg_time(__ui64_reg_time), last_login_time(__ui64_last_login_time) {}
                
                bool is_empty(){
                    return this->uid == -1;
                }
                
                static user_data empty(){
                    return {-1, "", "", "", user_type::admin, "", "", 0, 0};
                }
            } user_data;

        public:
            base(const std::filesystem::path& __c_fp_db_path);
            ~base();

            /**
             * Add a new user to database. UID will be given automatically.
             *
             * ATTENTION: pswd should be pre-hashed.
             */
            bool add_new_user(
                const std::string& __c_s_username, const std::string& __c_s_pswd, const std::string& __c_s_email = "",
                const std::string& __c_s_name = "", const std::string& __c_s_tag = ""
            );

            /**
             * Check if a user is admin.
             *
             * ATTENTION: If username doesn't exist, return false.
            */
            bool check_is_user_admin(const std::string& __c_s_username);

            /**
             * Check if a user is blocked.
             *
             * ATTENTION: If username doesn't exist, return false.
            */
            bool check_is_user_blocked(const std::string& __c_s_username);

            /**
             * Compare client provided login data with database.
             * This function should always be called first before `get_user_data()`.
             *
             * ATTENTION: pswd should be pre-hashed.
             * ATTENTION: This function only checks login data. If the user is blocked & not allowed to login, call `check_is_user_blocked()`.
            */
            bool check_login_data(const std::string& __c_s_username, const std::string& __c_s_pswd);
            
            /**
             * Close & release database manually.
             *
             * WARNING: Always call this function before exiting program!!! Destructing database automatically by `module_container` causes segmentation fault!!!
            */
            void close_database();
            std::string get_server_uuid() const noexcept;
            user_data get_user_data(int __i_uid);
            user_data get_user_data(const std::string& __c_s_username);
            bool has_uid(int __i_uid);
            bool has_username(const std::string& __c_s_username);

        private:
            std::filesystem::path _fp_db_path;
            std::unique_ptr<WCDB::Database> _p__db;

            std::string _s_server_uuid;

    }; // class base

} // namespace atina::server::core::database

#endif // __ATINA_SERVER_CORE_DATABASE_BASE_H__
