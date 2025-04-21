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
    if (_p__worker || _p__handle)
    {
        return;
    } // already inited

    _p__worker = g3::LogWorker::createLogWorker();
    _p__handle = std::move(_p__worker->addDefaultLogger("atina_server", folder::log()));

    g3::initializeLogging(_p__worker.get());
    _s_log_filename = _p__handle->call(&g3::FileSink::fileName).get();

    std::ostringstream oss;
    oss << "atina-server " << BUILD_CONFIG_VERSION << " [" << BUILD_CONFIG_BUILD_GIT_BRANCH << "@" << BUILD_CONFIG_BUILD_GIT_COMMIT << "]\n"
        << "logger initialized at " << time::now().to_str() << "\n\n";

    auto change_formatting = _p__handle->call(&g3::FileSink::overrideLogDetails, g3::LogMessage::FullLogDetailsToString);
    auto change_header = _p__handle->call(&g3::FileSink::overrideLogHeader, oss.str());
    change_formatting.wait();
    change_header.wait();

#ifdef ATINA_SERVER_DEBUG
    g3::only_change_at_initialization::addLogLevel(DEBUG, true);
#else // ATINA_SERVER_DEBUG
    g3::only_change_at_initialization::addLogLevel(DEBUG, false);
#endif // ATINA_SERVER_DEBUG
    g3::only_change_at_initialization::addLogLevel(INFO, true);
    g3::only_change_at_initialization::addLogLevel(WARNING, true);
    g3::only_change_at_initialization::addLogLevel(FATAL, true);

    return;
}

std::string log::filename() noexcept {
    return _s_log_filename;
}

std::string log::_s_log_filename;
std::unique_ptr<g3::LogWorker> log::_p__worker;
std::unique_ptr<g3::SinkHandle<g3::FileSink>> log::_p__handle;
