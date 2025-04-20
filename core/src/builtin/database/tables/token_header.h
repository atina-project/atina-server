#ifndef __ATINA_SERVER_CORE_BUILTIN_DATABASE_TABLES_TOKEN_HEADER_H__
#define __ATINA_SERVER_CORE_BUILTIN_DATABASE_TABLES_TOKEN_HEADER_H__

#include<cstdint>

#include"WCDB/CPPORMMacro.h"
#include"WCDB/WCDBCpp.h"

namespace atina::server::core::builtin::database::tables {

    class token_header {

        public:
            token_header(){}

            int i_version;  // database version
            uint64_t ui64_token_valid_time_length_ms;  // time length a token is valid after creation (in ms)
            uint64_t ui64_auto_cleanup_interval_min;  // tokens auto cleanup interval (in min)
            uint64_t ui64_last_cleanup_time;  // last token cleanup time (UTC-based timestamp)

            WCDB_CPP_ORM_DECLARATION(token_header)

    }; // class token_header

} // namespace atina::server::core::builtin::database::tables

#endif // __ATINA_SERVER_CORE_BUILTIN_DATABASE_TABLES_TOKEN_HEADER_H__
