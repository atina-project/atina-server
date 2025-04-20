#include"builtin/database/tables/token_header.h"

using namespace atina::server::core::builtin::database::tables;

WCDB_CPP_ORM_IMPLEMENTATION_BEGIN(token_header)

WCDB_CPP_SYNTHESIZE_COLUMN(i_version, "version")
WCDB_CPP_SYNTHESIZE_COLUMN(ui64_token_valid_time_length_ms, "token_valid_time_length")
WCDB_CPP_SYNTHESIZE_COLUMN(ui64_auto_cleanup_interval_min, "auto_cleanup_interval")
WCDB_CPP_SYNTHESIZE_COLUMN(ui64_last_cleanup_time, "last_cleanup_time")

WCDB_CPP_NOT_NULL(i_version)
WCDB_CPP_DEFAULT(ui64_token_valid_time_length_ms, 3600000)  // an hour
WCDB_CPP_NOT_NULL(ui64_token_valid_time_length_ms)
WCDB_CPP_DEFAULT(ui64_auto_cleanup_interval_min, 1)  // a minute
WCDB_CPP_NOT_NULL(ui64_auto_cleanup_interval_min)
WCDB_CPP_NOT_NULL(ui64_last_cleanup_time)

WCDB_CPP_ORM_IMPLEMENTATION_END
