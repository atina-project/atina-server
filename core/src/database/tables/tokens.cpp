#include"builtin/database/tables/tokens.h"

using namespace atina::server::core::builtin::database::tables;

WCDB_CPP_ORM_IMPLEMENTATION_BEGIN(tokens)

WCDB_CPP_SYNTHESIZE_COLUMN(i_id, "id")
WCDB_CPP_SYNTHESIZE_COLUMN(i_uid, "uid")
WCDB_CPP_SYNTHESIZE_COLUMN(s_token, "token")
WCDB_CPP_SYNTHESIZE_COLUMN(ui64_create_time, "create_time")
WCDB_CPP_SYNTHESIZE_COLUMN(ui64_expire_time, "expire_time")
WCDB_CPP_SYNTHESIZE_COLUMN(s_ip_addr, "ip_addr")
WCDB_CPP_SYNTHESIZE_COLUMN(s_user_agent, "user_agent")

WCDB_CPP_PRIMARY_ASC_AUTO_INCREMENT(i_id)
WCDB_CPP_NOT_NULL(i_uid)
WCDB_CPP_UNIQUE(i_uid)
WCDB_CPP_UNIQUE_INDEX("_uid", i_uid)
WCDB_CPP_NOT_NULL(s_token)
WCDB_CPP_NOT_NULL(ui64_create_time)
WCDB_CPP_NOT_NULL(ui64_expire_time)
WCDB_CPP_NOT_NULL(s_ip_addr)
WCDB_CPP_NOT_NULL(s_user_agent)

WCDB_CPP_ORM_IMPLEMENTATION_END
