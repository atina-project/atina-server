#include"core/utils/server_instance.h"

#include<fcntl.h>
#include<unistd.h>
#include<sys/file.h>

#include"g3log/g3log.hpp"

using namespace atina::server::core::utils;

const char* server_instance::LOCK_FILE_PATH = "/tmp/atina_server.lock";
std::vector<std::function<void()>> server_instance::__atexit_funcs;
std::vector<std::function<void()>> server_instance::__atfatal_funcs;

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

void server_instance::exit(){
    LOG(INFO) << "Exiting...";

    for (auto it = __atexit_funcs.rbegin() ; it != __atexit_funcs.rend(); ++it)
    {
        (*it)();
    }

    return;
}

void server_instance::register_atexit(const std::function<void()>& __c__func, bool __b_atfatal){
    __atexit_funcs.push_back(__c__func);
    if (__b_atfatal)
    {
        __atfatal_funcs.push_back(__c__func);
    }
    return;
}

void server_instance::_fatal(){
    for (auto it = __atfatal_funcs.rbegin() ; it != __atfatal_funcs.rend() ; ++it)
    {
        (*it)();
    }
    return;
}
