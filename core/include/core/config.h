#ifndef __ATINA_SERVER_CORE_CONFIG_H__
#define __ATINA_SERVER_CORE_CONFIG_H__

#include<filesystem>

namespace atina::server::core {

    class config {

        public:
            config();
            ~config(){}

            std::string admin_email() const noexcept;
            std::filesystem::path hook_send_email_script_path() const noexcept;

        private:
            std::string _s_admin_email;
            std::filesystem::path _fp_send_email_script_path;

            std::string _dump_config_to_string() const;

    }; // class config

} // namespace atina::server::core

#endif // __ATINA_SERVER_CORE_CONFIG_H__
