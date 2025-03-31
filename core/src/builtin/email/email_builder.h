#ifndef __ATINA_SERVER_CORE_BUILTIN_EMAIL_EMAIL_BUILDER_H__
#define __ATINA_SERVER_CORE_BUILTIN_EMAIL_EMAIL_BUILDER_H__

#include<filesystem>
#include<memory>

#include"builtin/database/base.h"
#include"core/config.h"
#include"core/enum.h"

namespace atina::server::core::builtin::email {

    class email_builder {

        public:
            email_builder(std::shared_ptr<config> __p__config, std::shared_ptr<database::base> __p__base_db);
            ~email_builder(){}

            std::filesystem::path build_verification_email(const std::string& __c_s_code, int __i_valid_timelen, lang __lang) const;
            std::filesystem::path build_welcome_email(const std::string& __c_s_username, lang __lang) const;

        private:
            std::string _s_admin_email;
            std::string _s_server_uuid;

    }; // class email_builder

} // namespace atina::server::core::builtin::email

#endif // __ATINA_SERVER_CORE_BUILTIN_EMAIL_EMAIL_BUILDER_H__
