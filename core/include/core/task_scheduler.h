#ifndef __ATINA_SERVER_CORE_TASK_SCHEDULER_H__
#define __ATINA_SERVER_CORE_TASK_SCHEDULER_H__

#include<condition_variable>
#include<functional>
#include<mutex>
#include<string>
#include<thread>
#include<unordered_map>

namespace atina::server::core {

    class task_scheduler {

        public:
            task_scheduler(){}
            ~task_scheduler();

            /**
             * Add a scheduled task into task scheduler, interval in minutes.
             * A task token will be returned.
             */
            std::string add_task(const std::string& __c_s_taskname, const std::function<void()> __c_fu_task, unsigned int __ui_interval_min, bool __b_exec_now = false);
            /**
             * Delete a scheduled task.
             * If you want to change task execute interval, delete it and then re-add it.
             */
            void delete_task(const std::string& __c_s_token);

            void start();
            void stop();

        private:
            typedef struct _task {
                std::string s_taskname;
                uint64_t ui64_next_exec_ts;
                uint64_t ui64_exec_interval_ms;
                std::function<void()> func;
            } _task;

        private:
            std::condition_variable _cv;
            std::mutex _mtx;
            std::unordered_map<std::string, _task> _tasks;
            std::thread _worker;

            bool _b_running;

            void _bg_task();

    }; // class task_scheduler

} // namespace atina::server::core

#endif // __ATINA_SERVER_CORE_TASK_SCHEDULER_H__
