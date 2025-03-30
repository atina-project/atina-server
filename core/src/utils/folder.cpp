#include"core/utils/folder.h"

#include"core/build_config.h"

using namespace atina::server::core::utils;
namespace fs = std::filesystem;

fs::path folder::config(){
    fs::path config = BUILD_CONFIG_CONFIG_DIR;
    if (!fs::exists(config))
    {
        fs::create_directories(config);
    }
    return config;
}

fs::path folder::data(){
    fs::path data = BUILD_CONFIG_DATA_DIR;
    if (!fs::exists(data))
    {
        fs::create_directories(data);
    }
    return data;
}

fs::path folder::log(){
    fs::path log = BUILD_CONFIG_LOG_DIR;
    if (!fs::exists(log))
    {
        fs::create_directories(log);
    }
    return log;
}

fs::path folder::script(){
    fs::path script = BUILD_CONFIG_SCRIPT_DIR;
    if (!fs::exists(script))
    {
        fs::create_directories(script);
    }
    return script;
}

fs::path folder::temp(){
    fs::path temp = fs::temp_directory_path();
    temp /= "atina";
    if (!fs::exists(temp))
    {
        fs::create_directories(temp);
    }
    return temp;
}
