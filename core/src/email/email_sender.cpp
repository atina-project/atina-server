#include"builtin/email/email_sender.h"

#include<boost/process.hpp>

#include"g3log/g3log.hpp"
#include"resources/resources.h"

using namespace atina::server::core::builtin::email;
namespace fs = std::filesystem;

bool email_sender::send_verification_code(const std::string& __c_s_receiver, const std::string& __c_s_code, int __i_valid_timelen, lang __lang) const {
    LOG(INFO) << "Sending verification code... [receiver=\"" << __c_s_receiver << "\",valid_timelen=" << __i_valid_timelen << ",lang=" << to_string(__lang) << "]";

    fs::path email_path = this->_p__builder->build_verification_email(__c_s_code, __i_valid_timelen, __lang);
    if (email_path.empty())
    {
        LOG(WARNING) << "Failed to send verification code: builder returned empty path.";
        return false;
    }
    std::string subject = resources::resource[to_string(__lang)]["core_builtin_email_verification_email_subject"];
    if (subject.empty())
    {
        subject = resources::resource["en"]["core_builtin_email_verification_email_subject"];
    }
    return this->_send(__c_s_receiver, subject, email_path);
}

bool email_sender::send_welcome(const std::string& __c_s_receiver, const std::string& __c_s_username, lang __lang) const {
    LOG(INFO) << "Sending welcome... [receiver=\"" << __c_s_receiver << "\",lang=" << to_string(__lang) << "]";

    fs::path email_path = this->_p__builder->build_welcome_email(__c_s_username, __lang);
    if (email_path.empty())
    {
        LOG(WARNING) << "Failed to send welcome: builder returned empty path.";
        return false;
    }
    std::string subject = resources::resource[to_string(__lang)]["core_builtin_email_welcome_email_subject"];
    if (subject.empty())
    {
        subject = resources::resource["en"]["core_builtin_email_welcome_email_subject"];
    }
    return this->_send(__c_s_receiver, subject, email_path);
}

bool email_sender::_send(const std::string& __c_s_receiver, const std::string& __c_s_subject, const fs::path& __c_fp_email) const {
    LOG(INFO) << "Calling send email script...";

    fs::path script_path = this->_p__config->hook_send_email_script_path();
    if (script_path.empty() || !fs::exists(script_path))
    {
        LOG(WARNING) << "Failed to call send email script: empty script path or non-exist script.";
        return false;
    }
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
    LOG(INFO) << "Send email script exited. [exit_code=" << ch.exit_code() << "]";
    return ch.exit_code() == 0;
}
