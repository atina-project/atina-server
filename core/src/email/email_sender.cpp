#include"builtin/email/email_sender.h"

#include<boost/process.hpp>

#include"resources/resources.h"

using namespace atina::server::core::builtin::email;
namespace fs = std::filesystem;

bool email_sender::send_verification_code(const std::string& __c_s_receiver, std::string __c_s_code, int __i_valid_timelen, email_builder::email_lang __lang){
    fs::path email_path = this->_p__builder->build_verification_email(__c_s_code, __i_valid_timelen, __lang);
    if (email_path.empty())
    {
        return false;
    }
    std::string subject;
    switch (__lang)
    {
        case email_builder::email_lang::en:   subject = resources::resource["en"]["core_builtin_email_verification_email_subject"]; break;
        case email_builder::email_lang::zhCN: subject = resources::resource["zhCN"]["core_builtin_email_verification_email_subject"]; break;
    }
    return this->_send(__c_s_receiver, subject, email_path);
}

bool email_sender::_send(const std::string& __c_s_receiver, const std::string& __c_s_subject, const fs::path& __c_fp_email){
    fs::path script_path = this->_p__config->hook_send_email_script_path();
    auto env = boost::this_process::environment();
    env["EMAIL_RECEIVER"] = __c_s_receiver;
    env["EMAIL_SUBJECT"] = __c_s_subject;
    env["EMAIL_PATH"] = __c_fp_email;
    env["EMAIL_TYPE"] = "HTML";
    boost::process::child ch(
        "/bin/bash", "-c", script_path.string(),
        boost::process::std_out > "/dev/null",
        boost::process::std_err > "/dev/null",
        env
    );
    // for now we don't need to capture stdout or stderr
    // but it might be good if we write them into log after introducing log (only if error occurs?)
    ch.wait();
    return ch.exit_code() == 0;
}
