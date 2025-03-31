#include"server/server.h"

#include"core/build_config.h"
#include"json/json.h"

using namespace atina::server::server;

std::string server::api_hi() const {
    Json::Value root;
    root["atina_server_version"] = BUILD_CONFIG_VERSION;
    root["atina_server_version_major"] = BUILD_CONFIG_VERSION_MAJOR;
    root["atina_server_version_minor"] = BUILD_CONFIG_VERSION_MINOR;
    root["atina_server_version_patch"] = BUILD_CONFIG_VERSION_PATCH;
    root["is_atina_server"] = true;
    return Json::FastWriter().write(root);
}
