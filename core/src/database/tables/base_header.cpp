#include"core/database/tables/base_header.h"

using namespace atina::server::core::database::tables;

WCDB_CPP_ORM_IMPLEMENTATION_BEGIN(base_header)

WCDB_CPP_SYNTHESIZE_COLUMN(i_version, "version")
WCDB_CPP_SYNTHESIZE_COLUMN(s_server_uuid, "server_uuid")
WCDB_CPP_SYNTHESIZE_COLUMN(ui64_create_time, "create_time")
WCDB_CPP_SYNTHESIZE_COLUMN(i_next_uid, "next_uid")

WCDB_CPP_NOT_NULL(i_version)
WCDB_CPP_NOT_NULL(s_server_uuid)
WCDB_CPP_NOT_NULL(ui64_create_time)
WCDB_CPP_DEFAULT(i_next_uid, 1)
WCDB_CPP_NOT_NULL(i_next_uid)

WCDB_CPP_ORM_IMPLEMENTATION_END
