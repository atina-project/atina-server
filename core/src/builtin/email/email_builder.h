#ifndef __ATINA_SERVER_CORE_BUILTIN_EMAIL_EMAIL_BUILDER_H__
#define __ATINA_SERVER_CORE_BUILTIN_EMAIL_EMAIL_BUILDER_H__

#include<filesystem>
#include<memory>

#include"builtin/database/base.h"

namespace atina::server::core::builtin::email {

    class email_builder {

        public:
            typedef enum email_lang {
                en,
                zhCN,
            } email_lang;

        public:
            email_builder(std::shared_ptr<database::base> __p__base_db);
            ~email_builder(){}

            std::filesystem::path build_verification_email(const std::string& __c_s_code, int __i_valid_timelen, email_lang __lang) const;

        private:
            std::string _s_server_uuid;

            std::string _convert_email_lang_to_string(email_lang __lang) const noexcept;

    }; // class email_builder

} // namespace atina::server::core::builtin::email

#endif // __ATINA_SERVER_CORE_BUILTIN_EMAIL_EMAIL_BUILDER_H__
