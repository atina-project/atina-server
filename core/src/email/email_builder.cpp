#include"builtin/email/email_builder.h"

#include<cerrno>
#include<cstring>
#include<fstream>
#include<sstream>

#include"builtin/database/base.h"
#include"core/utils/folder.h"
#include"core/utils/time.h"
#include"g3log/g3log.hpp"

using namespace atina::server::core::builtin::email;
namespace fs = std::filesystem;

email_builder::email_builder(std::shared_ptr<config> __p__config, std::shared_ptr<database::base> __p__base_db){
    this->_s_admin_email = __p__config->admin_email();
    this->_s_server_uuid = __p__base_db->get_server_uuid();
    return;
}

fs::path email_builder::build_verification_email(const std::string& __c_s_code, int __i_valid_timelen, lang __lang) const {
    fs::path template_path = utils::folder::data();
    template_path /= std::string("verification_code_").append(to_string(__lang))
                                                      .append(".html");
    if (!fs::exists(template_path))
    {
        LOG(WARNING) << "Verification code email template doesn't exist. [path=\"" << template_path << "\"]";
        return "";
    }

    std::ifstream rfile(template_path);
    if (!rfile.is_open())
    {
        LOG(WARNING) << "Failed to read from verification code email template. [path=\"" << template_path << "\",errno=" << errno << ",errmsg=\"" << std::strerror(errno) << "\"]";
        return "";
    }
    
    std::string buf;
    std::ostringstream oss;
    while (std::getline(rfile, buf))
    {
        oss << buf;
    }
    rfile.close();
    std::string email = oss.str();
    email.replace(email.find("@VERIFICATION_CODE@"), 19, __c_s_code);
    email.replace(email.find("@VALID_TIMELENGTH_MIN@"), 22, std::to_string(__i_valid_timelen));
    email.replace(email.find("@SERVER_UID@"), 12, this->_s_server_uuid);
    
    fs::path email_path = utils::folder::temp();
    email_path /= std::string("verification_code_").append(to_string(__lang))
                                                   .append("_")
                                                   .append(std::to_string(utils::time::now().to_ts()))
                                                   .append(".html");
    int count = 0;
    while (fs::exists(email_path))
    {
        std::string new_filename = (count == 0) ? email_path.filename()
                                                : email_path.stem();
        count++;
        new_filename.append(".").append(std::to_string(count));
        email_path = email_path.parent_path() / new_filename;
    } // avoid same filename
    LOG(INFO) << "Writing email to file. [path=\"" << email_path << "\"]";
    std::ofstream wfile(email_path);
    if (!wfile.is_open())
    {
        LOG(WARNING) << "Failed to write email to file. [path=\"" << email_path << "\",errno=" << errno << ",errmsg=\"" << std::strerror(errno) << "\"]";
        return "";
    }
    wfile << email;
    wfile.close();
    
    return email_path;
}

fs::path email_builder::build_welcome_email(const std::string& __c_s_username, lang __lang) const {
    fs::path template_path = utils::folder::data();
    template_path /= std::string("welcome_").append(to_string(__lang))
                                            .append(".html");
    if (!fs::exists(template_path))
    {
        LOG(WARNING) << "Welcome email template doesn't exist. [path=\"" << template_path << "\"]";
        return "";
    }

    std::ifstream rfile(template_path);
    if (!rfile.is_open())
    {
        LOG(WARNING) << "Failed to read from welcome email template. [path=\"" << template_path << "\",errno=" << errno << ",errmsg=\"" << std::strerror(errno) << "\"]";
        return "";
    }
    
    std::string buf;
    std::ostringstream oss;
    while (std::getline(rfile, buf))
    {
        oss << buf;
    }
    rfile.close();
    std::string email = oss.str();
    email.replace(email.find("@USERNAME@"), 10, __c_s_username);
    email.replace(email.find("@ADMIN_EMAIL@"), 13, this->_s_admin_email);

    fs::path email_path = utils::folder::temp();
    email_path /= std::string("welcome_").append(to_string(__lang))
                                         .append("_")
                                         .append(std::to_string(utils::time::now().to_ts()))
                                         .append(".html");
    int count = 0;
    while (fs::exists(email_path))
    {
        std::string new_filename = (count == 0) ? email_path.filename()
                                                : email_path.stem();
        count++;
        new_filename.append(".").append(std::to_string(count));
        email_path = email_path.parent_path() / new_filename;
    } // avoid same filename
    LOG(INFO) << "Writing email to file. [path=\"" << email_path << "\"]";
    std::ofstream wfile(email_path);
    if (!wfile.is_open())
    {
        LOG(WARNING) << "Failed to write email to file. [path=\"" << email_path << "\",errno=" << errno << ",errmsg=\"" << std::strerror(errno) << "\"]";
        return "";
    }
    wfile << email;
    wfile.close();
    
    return email_path;
}
