#include"core/database/base.h"

#include"core/database/tables/base_header.h"
#include"core/database/tables/users.h"
#include"core/enum.h"
#include"core/exception/database_exception.h"
#include"core/utils/hash/argon2.h"
#include"core/utils/time.h"
#include"core/utils/uuid.h"

using namespace atina::server::core;
namespace fs = std::filesystem;

database::base::base(const std::filesystem::path& __c_fp_db_path)
    : _fp_db_path(__c_fp_db_path)
{
    bool new_db = !fs::exists(this->_fp_db_path);
    this->_p__db = std::make_unique<WCDB::Database>(this->_fp_db_path.string());
    if (!this->_p__db->canOpen())
    {
        throw exception::database_exception(
            exception::database_errcode::DB_CANNOT_OPEN,
            "cannot open base db"
        );
    } // cannot open database

    if (new_db)
    {
        bool ret = this->_p__db->createTable<tables::base_header>("header");
        tables::base_header header;
        header.i_version = ATINA_SERVER_DATABASE_BASE_VERSION;
        header.s_server_uuid = utils::uuid::generate();
        header.ui64_create_time = utils::time::now().to_ts();
        header.i_next_uid = 1;
        ret &= this->_p__db->insertObject<tables::base_header>(header, "header");

        ret &= this->_p__db->createTable<tables::users>("users");
        tables::users admin;
        admin.i_uid = 0;
        admin.s_username = "admin";
        admin.s_pswd = utils::hash::argon2::hash("123456", header.s_server_uuid);
        admin.i_usertype = user_type::admin;
        admin.s_name = "Admin";
        admin.ui64_reg_time = utils::time::now().to_ts();
        ret &= this->_p__db->insertObject<tables::users>(admin, "users");

        if (!ret)
        {
            throw exception::database_exception(
                exception::database_errcode::DB_CREATION_FAILED,
                "failed to create new base db"
            );
        } // error occurs
    } // create new database
    else
    {
        bool ret = this->_p__db->tableExists("header").value();
        if (!ret)
        {
            throw exception::database_exception(
                exception::database_errcode::DB_TABLE_NOT_EXISTS,
                "header table doesn't exist in base db"
            );
        } // header table doesn't exist
        auto header = this->_p__db->getTable<tables::base_header>("header");
        auto version_optional = header.selectValue(
            WCDB_FIELD(tables::base_header::i_version),
            WCDB::Expression(),
            WCDB::OrderingTerms(),
            0
        );
        if (!version_optional.succeed())
        {
            throw exception::database_exception(
                exception::database_errcode::DB_GET_VALUE_FAILED,
                "failed to get version from header table in base db"
            );
        }
        // possible version sp judge should be added here
        auto server_uuid_optional = header.selectValue(
            WCDB_FIELD(tables::base_header::s_server_uuid),
            WCDB::Expression(),
            WCDB::OrderingTerms(),
            0
        );
        if (!server_uuid_optional.succeed())
        {
            throw exception::database_exception(
                exception::database_errcode::DB_GET_VALUE_FAILED,
                "failed to get server_uuid from header table in base db"
            );
        }
        this->_s_server_uuid = server_uuid_optional->textValue();
        
        ret = this->_p__db->tableExists("users").value();
        if (!ret)
        {
            throw exception::database_exception(
                exception::database_errcode::DB_TABLE_NOT_EXISTS,
                "users table doesn't exist in base db"
            );
        } // users table doesn't exist
        auto users = this->_p__db->getTable<tables::users>("users");
        auto all_user_data_optional = users.getAllObjects();
        if (!all_user_data_optional.succeed())
        {
            throw exception::database_exception(
                exception::database_errcode::DB_GET_VALUE_FAILED,
                "failed to get all datas from users table in base db"
            );
        }
        if (all_user_data_optional->size() < 1 || all_user_data_optional->front().i_uid != 0)
        {
            throw exception::database_exception(
                exception::database_errcode::DB_ILLEGAL_TABLE_DATA,
                "illegal users table in base db: admin user not found"
            );
        } // no user in table or admin user not found
    } // read existing database
    return;
}

bool database::base::add_new_user(const std::string& __c_s_username, const std::string& __c_s_pswd, const std::string& __c_s_email,
                                  const std::string& __c_s_name, const std::string& __c_s_tag)
{
    auto header = this->_p__db->getTable<tables::base_header>("header");
    int uid = header.selectValue(
        WCDB_FIELD(tables::base_header::i_next_uid),
        WCDB::Expression(),
        WCDB::OrderingTerms(),
        0
    )->intValue();
    bool ret = header.updateRow(
        uid + 1,
        WCDB_FIELD(tables::base_header::i_next_uid),
        WCDB::Expression(),
        WCDB::OrderingTerms(),
        WCDB::Expression(),
        0
    );
    if (!ret)
    {
        return false;
    } // update next_uid failed

    if (this->has_uid(uid) || this->has_username(__c_s_username))
    {
        return false;
    } // uid / username already exists
    tables::users new_user;
    new_user.i_uid = uid;
    new_user.s_username = __c_s_username;
    new_user.s_pswd = __c_s_pswd;
    new_user.s_email = __c_s_email;
    new_user.i_usertype = user_type::normal;
    new_user.s_name = __c_s_name;
    new_user.s_tag = __c_s_tag;
    new_user.ui64_reg_time = utils::time::now().to_ts();
    new_user.ui64_last_login_time = 0;
    ret = this->_p__db->insertObject<tables::users>(new_user, "users");
    if (!ret)
    {
        return false;
    } // insert new user failed

    return true;
}

bool database::base::check_login_data(const std::string& __c_s_username, const std::string& __c_s_pswd){
    if (!this->has_username(__c_s_username))
    {
        return false;
    } // username doesn't exist
    auto users = this->_p__db->getTable<tables::users>("users");
    auto user_pswd = users.getFirstObjectWithFields(
        WCDB_FIELD(tables::users::s_pswd),
        WCDB_FIELD(tables::users::s_username) == __c_s_username
    )->s_pswd;
    return __c_s_pswd == user_pswd;
}

std::string database::base::get_server_uuid() const noexcept {
    return this->_s_server_uuid;
}

database::base::user_data database::base::get_user_data(int __i_uid){
    if (!this->has_uid(__i_uid))
    {
        return user_data::empty();
    } // uid doesn't exist

    auto users = this->_p__db->getTable<tables::users>("users");
    auto user = users.getFirstObject(
        WCDB_FIELD(tables::users::i_uid) == __i_uid
    );
    return user_data(
        user->i_uid, user->s_username, user->s_pswd, user->s_email, user->i_usertype,
        user->s_name, user->s_tag, user->ui64_reg_time, user->ui64_last_login_time
    );
}

database::base::user_data database::base::get_user_data(const std::string& __c_s_username){
    if (!this->has_username(__c_s_username))
    {
        return user_data::empty();
    } // username doesn't exist

    auto users = this->_p__db->getTable<tables::users>("users");
    auto user = users.getFirstObject(
        WCDB_FIELD(tables::users::s_username) == __c_s_username
    );
    return user_data(
        user->i_uid, user->s_username, user->s_pswd, user->s_email, user->i_usertype,
        user->s_name, user->s_tag, user->ui64_reg_time, user->ui64_last_login_time
    );
}

bool database::base::has_uid(int __i_uid){
    bool has_user = this->_p__db->getValueFromStatement(
        WCDB::StatementSelect().select(1)
                               .from("users")
                               .where(WCDB_FIELD(tables::users::i_uid) == __i_uid)
                               .limit(1)
    )->boolValue();
    return has_user;
}

bool database::base::has_username(const std::string& __c_s_username){
    bool has_user = this->_p__db->getValueFromStatement(
        WCDB::StatementSelect().select(1)
                               .from("users")
                               .where(WCDB_FIELD(tables::users::s_username) == __c_s_username)
                               .limit(1)
    )->boolValue();
    return has_user;
}
