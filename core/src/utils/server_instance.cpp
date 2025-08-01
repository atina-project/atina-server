#include"core/utils/server_instance.h"

#include<fcntl.h>
#include<unistd.h>
#include<sys/file.h>

#include"g3log/g3log.hpp"

using namespace atina::server::core::utils;

const char* server_instance::LOCK_FILE_PATH = "/tmp/atina_server.lock";
std::vector<std::function<void()>> server_instance::_vfu_atexit_funcs;
std::vector<std::function<void()>> server_instance::_vfu_atfatal_funcs;

bool server_instance::ensure_single_instance(){
    LOG(INFO) << "Ensuring server single instance...";

    int lock_fd = open(LOCK_FILE_PATH, O_CREAT | O_RDWR, 0666);
    if (lock_fd == -1)
    {
        LOG(WARNING) << "Failed to open server lock file.";
        return false;
    }
    if (flock(lock_fd, LOCK_EX | LOCK_NB) == -1)
    {
        LOG(WARNING) << "Failed to lock server lock file.";
        close(lock_fd);
        return false;
    }
    return true;
}

void server_instance::exec_atexit_functions(){
    LOG(INFO) << "Exiting...";

    for (auto it = _vfu_atexit_funcs.rbegin() ; it != _vfu_atexit_funcs.rend(); ++it)
    {
        (*it)();
    }

    return;
}

void server_instance::add_atexit_function(const std::function<void()>& __c_fu_func, bool __b_atfatal){
    _vfu_atexit_funcs.push_back(__c_fu_func);
    if (__b_atfatal)
    {
        _vfu_atfatal_funcs.push_back(__c_fu_func);
    }
    return;
}

void server_instance::_exec_atfatal_functions(){
    for (auto it = _vfu_atfatal_funcs.rbegin() ; it != _vfu_atfatal_funcs.rend() ; ++it)
    {
        (*it)();
    }
    return;
}
