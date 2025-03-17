#include"core/utils/time.h"

#include<chrono>
#include<ctime>
#include<iomanip>
#include<sstream>

using namespace atina::server::core;

std::string utils::time::to_str() const {
    time_t s = this->_ui64_ts / 1000;
    int ms = this->_ui64_ts % 1000;
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&s), "%Y-%m-%d %H:%M:%S")
        << '.' << std::setw(3) << std::setfill('0') << ms;
    return oss.str();
}

uint64_t utils::time::to_ts(bool __b_no_ms) const noexcept {
    return __b_no_ms ? this->_ui64_ts / 1000 : this->_ui64_ts;
}

std::string utils::time::to_utc_str() const {
    time_t s = this->_ui64_ts / 1000;
    int ms = this->_ui64_ts % 1000;
    std::ostringstream oss;
    oss << std::put_time(std::gmtime(&s), "%Y-%m-%d %H:%M:%S")
        << '.' << std::setw(3) << std::setfill('0') << ms;
    return oss.str();
}

utils::time utils::time::now(){
    auto now = std::chrono::system_clock::now();
    auto ts_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return time(ts_ms);
}

int utils::time::timezone(){
    auto now = std::chrono::system_clock::now();
    std::time_t ts_s = std::chrono::system_clock::to_time_t(now);
    std::tm* local = std::localtime(&ts_s);
    int offset = local->tm_gmtoff;
    return offset / 60;
}

bool utils::operator<(utils::time __lhs, utils::time __rhs){
    return __lhs._ui64_ts < __rhs._ui64_ts;
}

bool utils::operator<=(utils::time __lhs, utils::time __rhs){
    return __lhs._ui64_ts <= __rhs._ui64_ts;
}

bool utils::operator==(utils::time __lhs, utils::time __rhs){
    return __lhs._ui64_ts == __rhs._ui64_ts;
}

bool utils::operator>(utils::time __lhs, utils::time __rhs){
    return __lhs._ui64_ts > __rhs._ui64_ts;
}

bool utils::operator>=(utils::time __lhs, utils::time __rhs){
    return __lhs._ui64_ts >= __rhs._ui64_ts;
}
