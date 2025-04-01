#ifndef __ATINA_SERVER_CORE_UTILS_SERVER_INSTANCE_H__
#define __ATINA_SERVER_CORE_UTILS_SERVER_INSTANCE_H__

namespace atina::server::core::utils {

    class server_instance {

        public:
            static bool ensure_single_instance();

        private:
            static const char* LOCK_FILE_PATH;

    }; // class server_instance

} // namespace atina::server::core::utils

#endif // __ATINA_SERVER_CORE_UTILS_SERVER_INSTANCE_H__
