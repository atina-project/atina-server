#include"core/utils/log.h"

#include<memory>
#include<sstream>

#include"core/build_config.h"
#include"core/utils/folder.h"
#include"core/utils/time.h"
#include"g3log/g3log.hpp"
#include"g3log/logworker.hpp"

using namespace atina::server::core::utils;

void log::init(){
    auto worker = g3::LogWorker::createLogWorker();
    auto handle = worker->addDefaultLogger("atina_server", folder::log());
    g3::initializeLogging(worker.get());
    _s_log_filename = handle->call(&g3::FileSink::fileName).get();

    std::ostringstream oss;
    oss << "atina-server " << BUILD_CONFIG_VERSION << " [" << BUILD_CONFIG_BUILD_GIT_BRANCH << "@" << BUILD_CONFIG_BUILD_GIT_COMMIT << "]\n"
        << "logger initialized at " << time::now().to_str() << "\n\n";

    auto change_formatting = handle->call(&g3::FileSink::overrideLogDetails, g3::LogMessage::FullLogDetailsToString);
    auto change_header = handle->call(&g3::FileSink::overrideLogHeader, oss.str());
    change_formatting.wait();
    change_header.wait();

#ifdef ATINA_SERVER_DEBUG
    g3::only_change_at_initialization::addLogLevel(DEBUG, true);
#else // ATINA_SERVER_DEBUG
    g3::only_change_at_initialization::addLogLevel(DEBUG, false);
#endif // ATINA_SERVER_DEBUG

    return;
}

std::string log::filename() noexcept {
    return _s_log_filename;
}

std::string log::_s_log_filename;
