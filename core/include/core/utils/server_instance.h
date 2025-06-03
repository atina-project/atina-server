#ifndef __ATINA_SERVER_CORE_UTILS_SERVER_INSTANCE_H__
#define __ATINA_SERVER_CORE_UTILS_SERVER_INSTANCE_H__

#include<functional>
#include<vector>

namespace atina::server::core::utils {

    class server_instance {

        public:
            static bool ensure_single_instance();
            static void exit();
            static void register_atexit(const std::function<void()>& __c_fu_func, bool __b_atfatal = true);

            static void _fatal();

        private:
            static const char* LOCK_FILE_PATH;

            static std::vector<std::function<void()>> _vfu_atexit_funcs;
            static std::vector<std::function<void()>> _vfu_atfatal_funcs;

    }; // class server_instance

} // namespace atina::server::core::utils

#endif // __ATINA_SERVER_CORE_UTILS_SERVER_INSTANCE_H__
