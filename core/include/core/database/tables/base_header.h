#ifndef __ATINA_SERVER_CORE_DATABASE_TABLES_BASE_HEADER_H__
#define __ATINA_SERVER_CORE_DATABASE_TABLES_BASE_HEADER_H__

#include<cstdint>

#include"WCDB/CPPORMMacro.h"
#include"WCDB/WCDBCpp.h"

namespace atina::server::core::database::tables {

    class base_header {

        public:
            base_header(){}

            int i_version;  // database version
            std::string s_server_uuid;  // server universal unique id, created on first startup
            uint64_t ui64_create_time;  // server create time (UTC-based timestamp)
            int i_next_uid;  // next user id given to new registered user, will not rollback

            WCDB_CPP_ORM_DECLARATION(base_header)

    }; // class base_header

} // namespace atina::server::core::database::tables

#endif // __ATINA_SERVER_CORE_DATABASE_TABLES_BASE_HEADER_H__
