#include"core/config.h"

#include<cerrno>
#include<cstring>
#include<fstream>
#include<sstream>

#include"core/build_config.h"
#include"core/exception/config_exception.h"
#include"core/utils/folder.h"
#include"g3log/g3log.hpp"
#include"json/json.h"

using namespace atina::server::core;
namespace fs = std::filesystem;

config::config(){
    fs::path config_path = fs::path(BUILD_CONFIG_CONFIG_DIR);
    if (!fs::exists(config_path))
    {
        fs::create_directories(config_path);
    }
    if (!fs::is_directory(config_path))
    {
        throw exception::config_exception(
            exception::config_errcode::CFG_FOLDER_IS_NOT_DIR,
            "config folder is not a directory"
        );
    }

#if BUILD_CONFIG_USE_BUILTIN_GMAIL
    this->_fp_send_email_script_path = utils::folder::script() / "send_email.sh";
    if (!fs::exists(this->_fp_send_email_script_path))
    {
        this->_fp_send_email_script_path.clear();
    } // using builtin gmail but default send email script doesn't exist
#endif // BUILD_CONFIG_USE_BUILTIN_GMAIL
    this->_ui_validation_code_valid_time_length_min = 10;

    config_path /= "server_config.json";
    if (!fs::exists(config_path))
    {
        LOG(INFO) << "Creating new config file... [path=" << config_path << "]";
        Json::Value root;
        root["admin_email"] = this->_s_admin_email;
        root["send_email_script_path"] = this->_fp_send_email_script_path.string();
        root["validation_code_style"] = this->_i_validation_code_style;
        root["validation_code_valid_time_length_min"] = this->_ui_validation_code_valid_time_length_min;

        std::ofstream config_file(config_path);
        if (!config_file.is_open())
        {
            LOG(WARNING) << "Failed to write to new config file. [path=" << config_path << ",errno=" << errno << ",errmsg=\"" << std::strerror(errno) << "\"]";
            throw exception::config_exception(
                exception::config_errcode::CFG_CANNOT_OPEN,
                "cannot open server_config.json to write"
            );
        }
        Json::StreamWriterBuilder writer;
        writer["indentation"] = "    ";
        config_file << Json::writeString(writer, root);
        config_file.close();
    } // new config
    else
    {
        LOG(INFO) << "Reading from config file... [path=" << config_path << "]";
        std::ifstream config_file(config_path);
        if (!config_file.is_open())
        {
            LOG(WARNING) << "Failed to read from config file. [path=" << config_path << ",errno=" << errno << ",errmsg=\"" << std::strerror(errno) << "\"]";
            throw exception::config_exception(
                exception::config_errcode::CFG_CANNOT_OPEN,
                "cannot open server_config.json to read"
            );
        }

        Json::Value root;
        Json::CharReaderBuilder reader;
        std::string err;
        if (!Json::parseFromStream(reader, config_file, &root, &err))
        {
            LOG(WARNING) << "Illegal config file format, use default. [errmsg=\"" << err << "\"]";
            config_file.close();
            LOG(INFO) << "Config parse done. [" << this->_dump_config_to_string() << "]";
            return;
        } // parse failed, use default
        config_file.close();

        this->_s_admin_email = root["admin_email"].asString();
        this->_fp_send_email_script_path = root["send_email_script_path"].asString();
        this->_i_validation_code_style = root["validation_code_style"].asInt();
        this->_ui_validation_code_valid_time_length_min = root["validation_code_valid_time_length_min"].asUInt();
    }

    LOG(INFO) << "Config parse done. [" << this->_dump_config_to_string() << "]";
    return;
}

std::string config::admin_email() const noexcept {
    return this->_s_admin_email;
}

fs::path config::hook_send_email_script_path() const noexcept {
    return this->_fp_send_email_script_path;
}

int config::validation_code_style() const noexcept {
    return this->_i_validation_code_style;
}

unsigned int config::validation_code_valid_time_length_min() const noexcept {
    return this->_ui_validation_code_valid_time_length_min;
}

std::string config::_dump_config_to_string() const {
    std::ostringstream oss;
    oss << "admin_email=\"" << this->_s_admin_email << "\","
        << "send_email_script_path=\"" << this->_fp_send_email_script_path << "\","
        << "validation_code_style=" << this->_i_validation_code_style << ","
        << "validation_code_valid_time_length_min=" << this->_ui_validation_code_valid_time_length_min;
    return oss.str();
}
