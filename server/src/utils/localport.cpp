#include"server/utils/localport.h"

#include<fstream>
#include<sstream>
#include<unistd.h>

using namespace atina::server::server::utils;

bool localport::check_tcp_can_occupy(int __i_port){
    return _check_can_occupy(__i_port, "/proc/net/tcp", "/proc/net/tcp6");
}

bool localport::check_udp_can_occupy(int __i_port){
    return _check_can_occupy(__i_port, "/proc/net/udp", "/proc/net/udp6");
}

bool localport::_check_can_occupy(int __i_port, const std::string& __c_s_v4file, const std::string& __c_s_v6file){
    if (__i_port < 0 || __i_port > 65535)
    {
        return false;
    } // illegal port
    if (getuid() != 0 && __i_port < 1024)
    {
        return false;
    } // use port < 1024 without root

    std::string line;

    std::ifstream v4file(__c_s_v4file);
    if (!v4file.is_open())
    {
        return false;
    }
    std::getline(v4file, line);
    // ignore header line
    while (std::getline(v4file, line))
    {
        std::istringstream iss(line);
        std::string sl, local_addr, remote_addr, st;
        if (!(iss >> sl >> local_addr >> remote_addr >> st))
        {
            continue;
        } // parse line failed
        size_t colon_pos = local_addr.find(':');
        if (colon_pos == std::string::npos)
        {
            continue;
        }
        std::string addr = local_addr.substr(0, colon_pos);
        int port = _parse_hex_port_to_dec(local_addr.substr(colon_pos + 1));
        if (addr == "0100007F" /* 127.0.0.1 */ && __i_port == port)
        {
            v4file.close();
            return false;
        }
    }
    v4file.close();

    std::ifstream v6file(__c_s_v6file);
    if (!v6file.is_open())
    {
        return false;
    }
    std::getline(v6file, line);
    // ignore header line
    while (std::getline(v6file, line))
    {
        std::istringstream iss(line);
        std::string sl, local_addr, remote_addr, st;
        if (!(iss >> sl >> local_addr >> remote_addr >> st))
        {
            continue;
        } // parse line failed
        size_t colon_pos = local_addr.find(':');
        if (colon_pos == std::string::npos)
        {
            continue;
        }
        std::string addr = local_addr.substr(0, colon_pos);
        int port = _parse_hex_port_to_dec(local_addr.substr(colon_pos + 1));
        if (addr == "00000000000000000000000001000000" /* ::1 */ && __i_port == port)
        {
            v6file.close();
            return false;
        }
    }
    v6file.close();

    return true;
}

int localport::_parse_hex_port_to_dec(const std::string __c_s_hex_port){
    int port;
    std::stringstream ss;
    ss << std::hex << __c_s_hex_port;
    ss >> port;
    return port;
}
