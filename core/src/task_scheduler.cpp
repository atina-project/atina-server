#include"core/task_scheduler.h"

#include"core/utils/time.h"
#include"g3log/g3log.hpp"

using namespace atina::server::core;

task_scheduler::~task_scheduler(){
    this->stop();
    return;
}

int task_scheduler::add_task(const std::string& __c_s_taskname, const std::function<void()>& __c_fu_task, unsigned int __ui_interval_min, bool __b_exec_now){
    std::lock_guard<std::mutex> lock(this->_mtx);

    int token = this->_i_next_token;
    this->_i_next_token++;

    _task this_task;
    this_task.s_taskname = __c_s_taskname;
    this_task.ui64_exec_interval_ms = __ui_interval_min * 60 * 1000;
    this_task.ui64_next_exec_ts = utils::time::now().to_ts() + this_task.ui64_exec_interval_ms;
    this_task.func = __c_fu_task;
    this->_tasks[token] = this_task;

    if (__b_exec_now)
    {
        __c_fu_task();
    }

    return token;
}

void task_scheduler::delete_task(int __i_token){
    std::lock_guard<std::mutex> lock(this->_mtx);

    auto it = this->_tasks.find(__i_token);
    if (it != this->_tasks.end())
    {
        this->_tasks.erase(it);
    }
    return;
}

void task_scheduler::start(){
    std::lock_guard<std::mutex> lock(this->_mtx);

    if (this->_b_running)
    {
        return;
    }
    this->_b_running = true;
    this->_worker = std::thread(&task_scheduler::_bg_task, this);
    return;
}

void task_scheduler::stop(){
    {
        std::lock_guard<std::mutex> lock(this->_mtx);
        if (!this->_b_running)
        {
            return;
        }
        this->_b_running = false;
    }

    this->_cv.notify_one();
    this->_worker.join();
    return;
}

void task_scheduler::_bg_task(){
    std::unique_lock<std::mutex> lock(this->_mtx);
    while (this->_b_running)
    {
        this->_cv.wait_for(lock, std::chrono::seconds(10), [this]{
            return !this->_b_running;
        });
        LOG(DEBUG) << "Checking need-to-execute background tasks...";
        uint64_t now = utils::time::now().to_ts();
        for (auto& it : this->_tasks)
        {
            if (it.second.ui64_next_exec_ts <= now)
            {
                LOG(INFO) << "Executing background task... [taskname=\"" << it.second.s_taskname << "\"]";
                it.second.func();
                it.second.ui64_next_exec_ts += it.second.ui64_exec_interval_ms;
                LOG(INFO) << "Background task executed. [taskname=\"" << it.second.s_taskname << "\",next_ts=" << it.second.ui64_next_exec_ts << "]";
            }
        }
    } // background worker is triggered every 10 seconds
    return;
}
