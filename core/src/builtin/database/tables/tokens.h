#ifndef __ATINA_SERVER_CORE_BUILTIN_DATABASE_TABLES_TOKENS_H__
#define __ATINA_SERVER_CORE_BUILTIN_DATABASE_TABLES_TOKENS_H__

#include<cstdint>

#include"WCDB/CPPORMMacro.h"
#include"WCDB/WCDBCpp.h"

namespace atina::server::core::builtin::database::tables {

    class tokens {

        public:
            tokens(){}

            int i_id;  // id primary key
            int i_uid;  // user id
            std::string s_token;  // current access token
            uint64_t ui64_create_time;  // token create time (UTC-based timestamp)
            uint64_t ui64_expire_time;  // token expire time (UTC-based timestamp)
            std::string s_ip_addr;  // client ip address
            std::string s_user_agent;  // client user agent
            // additional client verification like device fingerprint isn't so necessary for such a small project...

            WCDB_CPP_ORM_DECLARATION(tokens)

    }; // class tokens

} // namespace atina::server::core::builtin::database::tables

#endif // __ATINA_SERVER_CORE_BUILTIN_DATABASE_TABLES_TOKENS_H__
