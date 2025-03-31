#ifndef __ATINA_SERVER_SERVER_UTILS_LOCALPORT_H__
#define __ATINA_SERVER_SERVER_UTILS_LOCALPORT_H__

#include<string>

namespace atina::server::server::utils {

    class localport {

        public:
            /**
             * Check `/proc/net/tcp` & `/proc/net/tcp6` to see if port can be used.
             * If an illegal port (port < 0 || port > 65535) is given, false will be returned.
             *
             * ATTENTION: If a port < 1024 is given & process is not run in root, false will be returned.
             */
            static bool check_tcp_can_occupy(int __i_port);

            /**
             * Check `/proc/net/udp` & `/proc/net/udp6` to see if port can be used.
             * If an illegal port (port < 0 || port > 65535) is given, false will be returned.
             *
             * ATTENTION: If a port < 1024 is given & process is not run in root, false will be returned.
             */
            static bool check_udp_can_occupy(int __i_port);

        private:
            static bool _check_can_occupy(int __i_port, const std::string& __c_s_v4file, const std::string& __c_s_v6file);
            static int _parse_hex_port_to_dec(const std::string __c_s_hex_port);

    }; // class localport

} // namespace atina::server::server::utils

#endif // __ATINA_SERVER_SERVER_UTILS_LOCALPORT_H__
