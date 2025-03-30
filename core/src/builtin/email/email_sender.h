#ifndef __ATINA_SERVER_CORE_BUILTIN_EMAIL_EMAIL_SENDER_H__
#define __ATINA_SERVER_CORE_BUILTIN_EMAIL_EMAIL_SENDER_H__

#include<filesystem>
#include<memory>

#include"builtin/email/email_builder.h"
#include"core/config.h"
#include"core/enum.h"

namespace atina::server::core::builtin::email {

    class email_sender {

        public:
            email_sender(std::shared_ptr<email_builder> __p__builder, std::shared_ptr<config> __p__config)
                : _p__builder(__p__builder), _p__config(__p__config){}
            ~email_sender(){}

            bool send_verification_code(const std::string& __c_s_receiver, std::string __c_s_code, int __i_valid_timelen, lang __lang);

        private:
            std::shared_ptr<email_builder> _p__builder;
            std::shared_ptr<config> _p__config;

            bool _send(const std::string& __c_s_receiver, const std::string& __c_s_subject, const std::filesystem::path& __c_fp_email);

    }; // class email_sender

} // namespace atina::server::core::builtin::email

#endif // __ATINA_SERVER_CORE_BUILTIN_EMAIL_EMAIL_SENDER_H__
