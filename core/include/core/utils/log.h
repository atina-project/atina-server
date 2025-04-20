#ifndef __ATINA_SERVER_CORE_UTILS_LOG_H__
#define __ATINA_SERVER_CORE_UTILS_LOG_H__

#include<string>

namespace atina::server::core::utils {

    class log {

        public:
            static void init();

            static std::string filename() noexcept;

        private:
            static std::string _s_log_filename;

    }; // class log

} // namespace atina::server::core::utils

#endif // __ATINA_SERVER_CORE_UTILS_LOG_H__
