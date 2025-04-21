#ifndef __ATINA_SERVER_CORE_UTILS_LOG_H__
#define __ATINA_SERVER_CORE_UTILS_LOG_H__

#include<memory>
#include<string>

namespace g3 {

    class FileSink;
    class LogWorker;
    template<typename T> class SinkHandle;

} // namespace g3

namespace atina::server::core::utils {

    class log {

        public:
            static void init();

            static std::string filename() noexcept;

        private:
            static std::string _s_log_filename;
            static std::unique_ptr<g3::LogWorker> _p__worker;
            static std::unique_ptr<g3::SinkHandle<g3::FileSink>> _p__handle;

    }; // class log

} // namespace atina::server::core::utils

#endif // __ATINA_SERVER_CORE_UTILS_LOG_H__
