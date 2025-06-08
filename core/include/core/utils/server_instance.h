#ifndef __ATINA_SERVER_CORE_UTILS_SERVER_INSTANCE_H__
#define __ATINA_SERVER_CORE_UTILS_SERVER_INSTANCE_H__

#include<functional>
#include<vector>

namespace atina::server::core::utils {

    class server_instance {

        public:
            static bool ensure_single_instance();

            /**
             * Add a function which should be execed at exit.
             * Functions follow LIFO rule.
             * If the function shouldn't be run on crash, set `__b_atfatal` as false.
             */
            static void add_atexit_function(const std::function<void()>& __c_fu_func, bool __b_atfatal = true);
            static void exec_atexit_functions();
            /**
             * This function should only used as g3log fatal pre logging hook (`g3::setFatalPreLoggingHook()`).
             * DO NOT call this function manually!!!
             */
            static void _exec_atfatal_functions();

        private:
            static const char* LOCK_FILE_PATH;

            static std::vector<std::function<void()>> _vfu_atexit_funcs;
            static std::vector<std::function<void()>> _vfu_atfatal_funcs;

    }; // class server_instance

} // namespace atina::server::core::utils

#endif // __ATINA_SERVER_CORE_UTILS_SERVER_INSTANCE_H__
