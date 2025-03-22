#ifndef __ATINA_SERVER_CORE_BUILTIN_DATABASE_TABLES_USERS_H__
#define __ATINA_SERVER_CORE_BUILTIN_DATABASE_TABLES_USERS_H__

#include<cstdint>
#include<string>

#include"core/enum.h"
#include"WCDB/CPPORMMacro.h"
#include"WCDB/WCDBCpp.h"

namespace atina::server::core::builtin::database::tables {

    class users {

        public:
            users(){}

            int i_uid;  // user id given by server, global unique (in server)
            std::string s_username;  // username for login
            std::string s_pswd;  // user password (stored in Argon2 hash)
            std::string s_email;  // user email
            user_type i_usertype;  // user type (admin, normal, etc.)
            std::string s_name;  // username displayed in foreground
            std::string s_tag;  // user tag given by admin
            uint64_t ui64_reg_time;  // register time (UTC-based timestamp)
            uint64_t ui64_last_login_time;  // last login time (UTC-based timestamp)

            WCDB_CPP_ORM_DECLARATION(users)

    }; // class users

} // namespace atina::server::core::builtin::database::tables

#endif // __ATINA_SERVER_CORE_BUILTIN_DATABASE_TABLES_USERS_H__
