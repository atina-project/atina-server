#include"core/config.h"

#include<fstream>

#include"core/build_config.h"
#include"core/exception/config_exception.h"
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

    config_path /= "server_config.json";
    if (!fs::exists(config_path))
    {
        Json::Value root;
        root["send_email_script_path"] = this->_fp_send_email_script_path.string();

        std::ofstream config_file(config_path);
        if (!config_file.is_open())
        {
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
        std::ifstream config_file(config_path);
        if (!config_file.is_open())
        {
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
            return;
        } // parse failed, use default
        config_file.close();

        this->_fp_send_email_script_path = root["send_email_script_path"].asString();
    }

    return;
}

fs::path config::hook_send_email_script_path() const noexcept {
    return this->_fp_send_email_script_path;
}
