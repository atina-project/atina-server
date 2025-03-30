#include"builtin/email/email_builder.h"

#include<fstream>
#include<sstream>

#include"builtin/database/base.h"
#include"core/utils/folder.h"
#include"core/utils/time.h"

using namespace atina::server::core::builtin::email;
namespace fs = std::filesystem;

email_builder::email_builder(std::shared_ptr<database::base> __p__base_db){
    this->_s_server_uuid = __p__base_db->get_server_uuid();
    return;
}

fs::path email_builder::build_verification_email(const std::string& __c_s_code, int __i_valid_timelen, lang __lang) const {
    fs::path template_path = utils::folder::data();
    template_path /= std::string("verification_code_").append(to_string(__lang))
                                                      .append(".html");
    if (!fs::exists(template_path))
    {
        return "";
    }

    std::ifstream rfile(template_path);
    if (!rfile.is_open())
    {
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
    std::ofstream wfile(email_path);
    if (!wfile.is_open())
    {
        return "";
    }
    wfile << email;
    wfile.close();
    
    return email_path;
}
