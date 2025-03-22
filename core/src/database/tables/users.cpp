#include"builtin/database/tables/users.h"

using namespace atina::server::core::builtin::database::tables;

WCDB_CPP_ORM_IMPLEMENTATION_BEGIN(users)

WCDB_CPP_SYNTHESIZE_COLUMN(i_uid, "uid")
WCDB_CPP_SYNTHESIZE_COLUMN(s_username, "username")
WCDB_CPP_SYNTHESIZE_COLUMN(s_pswd, "pswd")
WCDB_CPP_SYNTHESIZE_COLUMN(s_email, "email")
WCDB_CPP_SYNTHESIZE_COLUMN(i_usertype, "usertype")
WCDB_CPP_SYNTHESIZE_COLUMN(s_name, "name")
WCDB_CPP_SYNTHESIZE_COLUMN(s_tag, "tag")
WCDB_CPP_SYNTHESIZE_COLUMN(ui64_reg_time, "reg_time")
WCDB_CPP_SYNTHESIZE_COLUMN(ui64_last_login_time, "last_login_time")

WCDB_CPP_PRIMARY_ASC(i_uid)
WCDB_CPP_NOT_NULL(s_username)
WCDB_CPP_UNIQUE(s_username)
WCDB_CPP_UNIQUE_INDEX("_username", s_username)
WCDB_CPP_NOT_NULL(s_pswd)
WCDB_CPP_NOT_NULL(i_usertype)
WCDB_CPP_INDEX("_usertype", i_usertype)
WCDB_CPP_NOT_NULL(s_name)
WCDB_CPP_INDEX("_name", s_name)
WCDB_CPP_NOT_NULL(ui64_reg_time)

WCDB_CPP_ORM_IMPLEMENTATION_END
