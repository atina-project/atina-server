#include"core/utils/server_instance.h"

#include<fcntl.h>
#include<unistd.h>
#include<sys/file.h>

#include"g3log/g3log.hpp"

using namespace atina::server::core::utils;

const char* server_instance::LOCK_FILE_PATH = "/tmp/atina_server.lock";

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
