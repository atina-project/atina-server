#include"builtin/database/token.h"

#include<cassert>
#include<chrono>

#include"builtin/database/tables/token_header.h"
#include"builtin/database/tables/tokens.h"
#include"core/exception/database_exception.h"
#include"core/utils/time.h"
#include"core/utils/uuid.h"

using namespace atina::server::core::builtin;
namespace fs = std::filesystem;

database::token::token(const fs::path& __c_fp_db_path)
    : _fp_db_path(__c_fp_db_path)
{
    bool new_db = !fs::exists(this->_fp_db_path);
    this->_p__db = std::make_unique<WCDB::Database>(this->_fp_db_path.string());
    if (!this->_p__db->canOpen())
    {
        throw exception::database_exception(
            exception::database_errcode::DB_CANNOT_OPEN,
            "cannot open token db"
        );
    } // cannot open database

    if (new_db)
    {
        bool ret = this->_p__db->createTable<tables::token_header>("header");
        tables::token_header header;
        header.i_version = ATINA_SERVER_DATABASE_TOKEN_VERSION;
        header.ui64_token_valid_time_length = 3600000;
        header.ui64_auto_cleanup_interval = 60000;
        header.ui64_last_cleanup_time = utils::time::now().to_ts();
        ret &= this->_p__db->insertObject<tables::token_header>(header, "header");

        ret &= this->_p__db->createTable<tables::tokens>("tokens");

        if (!ret)
        {
            throw exception::database_exception(
                exception::database_errcode::DB_CREATION_FAILED,
                "failed to create new token db"
            );
        } // error occurs

        this->_ui64_token_valid_time_length = 3600000;
        this->_ui64_auto_cleanup_interval = 60000;
        this->_ui64_last_cleanup_time = header.ui64_last_cleanup_time;
    } // create new database
    else
    {
        bool ret = this->_p__db->tableExists("header").value();
        if (!ret)
        {
            throw exception::database_exception(
                exception::database_errcode::DB_TABLE_NOT_EXISTS,
                "header table doesn't exist in token db"
            );
        } // header table doesn't exist
        auto header = this->_p__db->getTable<tables::token_header>("header");
        auto header_data_optional = header.getFirstObject();
        if (!header_data_optional.succeed())
        {
            throw exception::database_exception(
                exception::database_errcode::DB_GET_VALUE_FAILED,
                "failed to get data from header table in token db"
            );
        }
        // possible version sp judge should be added here
        this->_ui64_token_valid_time_length = header_data_optional->ui64_token_valid_time_length;
        this->_ui64_auto_cleanup_interval = header_data_optional->ui64_auto_cleanup_interval;
        this->_ui64_last_cleanup_time = header_data_optional->ui64_last_cleanup_time;

        ret = this->_p__db->tableExists("tokens").value();
        if (!ret)
        {
            throw exception::database_exception(
                exception::database_errcode::DB_TABLE_NOT_EXISTS,
                "tokens table doesn't exist in token db"
            );
        } // tokens table doesn't exist
        if (!this->_p__db->getAllObjects<tables::tokens>("tokens").succeed())
        {
            throw exception::database_exception(
                exception::database_errcode::DB_ILLEGAL_TABLE_DATA,
                "failed to get all datas from tokens table in token db"
            );
        } // illegal tokens table

        this->cleanup_database();
    } // read existing database
    return;
}

database::token::~token(){
    this->stop_bg_auto_cleanup();
    this->close_database();
    return;
}

std::string database::token::add_token(int __i_uid, const std::string& __c_s_ip_addr, const std::string& __c_s_user_agent){
    assert(this->_p__db);
    std::lock_guard<std::recursive_mutex> lock(this->_mtx);

    auto tokens = this->_p__db->getTable<tables::tokens>("tokens");
    
    if (this->has_uid(__i_uid))
    {
        auto expire_time = tokens.getFirstObjectWithFields(
            WCDB_FIELD(tables::tokens::ui64_expire_time),
            WCDB_FIELD(tables::tokens::i_uid) == __i_uid
        )->ui64_expire_time;
        if (expire_time > utils::time::now().to_ts())
        {
            return "";
        } // token exists and not expired
        tokens.deleteObjects(
            WCDB_FIELD(tables::tokens::i_uid) == __i_uid
        );
    } // uid exists

    tables::tokens new_token;
    new_token.isAutoIncrement = true;
    new_token.i_uid = __i_uid;
    new_token.s_token = utils::uuid::generate();
    new_token.ui64_create_time = utils::time::now().to_ts();
    new_token.ui64_expire_time = new_token.ui64_create_time + this->_ui64_token_valid_time_length;
    new_token.s_ip_addr = __c_s_ip_addr;
    new_token.s_user_agent = __c_s_user_agent;
    bool ret = tokens.insertObject(new_token);
    if (!ret)
    {
        return "";
    }

    return new_token.s_token;
}

bool database::token::check_token_if_valid_refresh_expired_remove(int __i_uid, const std::string& __c_s_token){
    assert(this->_p__db);
    std::lock_guard<std::recursive_mutex> lock(this->_mtx);

    if (!this->has_uid(__i_uid))
    {
        return false;
    } // uid doesn't exist: not requested or already expired

    auto tokens = this->_p__db->getTable<tables::tokens>("tokens");
    auto token = tokens.getFirstObject(
        WCDB_FIELD(tables::tokens::i_uid) == __i_uid
    );
    if (token->ui64_expire_time <= utils::time::now().to_ts())
    {
        tokens.deleteObjects(
            WCDB_FIELD(tables::tokens::i_uid) == __i_uid
        );
        return false;
    } // expired, remove
    else if (!utils::uuid::compare(token->s_token, __c_s_token))
    {
        return false;
    } // wrong token
    {
        bool ret = tokens.updateRow(
            utils::time::now().to_ts() + this->_ui64_token_valid_time_length,
            WCDB_FIELD(tables::tokens::ui64_expire_time),
            WCDB_FIELD(tables::tokens::i_uid) == __i_uid
        );
        return ret;
    } // valid, refresh
}

bool database::token::cleanup_database(){
    assert(this->_p__db);
    std::lock_guard<std::recursive_mutex> lock(this->_mtx);

    auto token_header = this->_p__db->getTable<tables::token_header>("header");
    auto tokens = this->_p__db->getTable<tables::tokens>("tokens");
    uint64_t now_ts = utils::time::now().to_ts();
    bool ret = this-_p__db->runTransaction([&](WCDB::Handle&){
        bool ret = tokens.deleteObjects(
            WCDB_FIELD(tables::tokens::ui64_expire_time) <= now_ts
        );
        ret &= token_header.updateRow(
            now_ts,
            WCDB_FIELD(tables::token_header::ui64_last_cleanup_time),
            WCDB::Expression(),
            WCDB::OrderingTerms(),
            WCDB::Expression(),
            0
        );
        return ret;
    });
    return ret;
}

void database::token::close_database(){
    std::lock_guard<std::recursive_mutex> lock(this->_mtx);

    if (this->_p__db)
    {
        this->_p__db->close();
        this->_p__db.reset();
    }
    return;
}

bool database::token::has_uid(int __i_uid){
    assert(this->_p__db);
    std::lock_guard<std::recursive_mutex> lock(this->_mtx);

    bool has_uid = this->_p__db->getValueFromStatement(
        WCDB::StatementSelect().select(1)
                               .from("tokens")
                               .where(WCDB_FIELD(tables::tokens::i_uid) == __i_uid)
                               .limit(1)
    )->boolValue();
    return has_uid;
}

void database::token::start_bg_auto_cleanup(){
    std::lock_guard<std::mutex> lock(this->_mtx_bg);

    if (this->_b_bg_running)
    {
        return;
    }
    this->_b_bg_running = true;
    this->_t_bg_worker = std::thread(&token::_bg_auto_cleanup_task, this);
    return;
}

void database::token::stop_bg_auto_cleanup(){
    {
        std::lock_guard<std::mutex> lock(this->_mtx_bg);
        if (!this->_b_bg_running)
        {
            return;
        }
        this->_b_bg_running = false;
    }
    this->_cv_bg.notify_one();
    this->_t_bg_worker.join();
    return;
}

void database::token::_bg_auto_cleanup_task(){
    std::unique_lock<std::mutex> lock(this->_mtx_bg);
    while (this->_b_bg_running)
    {
        this->_cv_bg.wait_for(lock, std::chrono::milliseconds(this->_ui64_auto_cleanup_interval), [this]{
            return !this->_b_bg_running;
        });
        this->cleanup_database();
    }
    return;
}
