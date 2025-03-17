#ifndef __ATINA_SERVER_CORE_UTILS_TIME_H__
#define __ATINA_SERVER_CORE_UTILS_TIME_H__

#include<cstdint>
#include<string>

namespace atina::server::core::utils {

    class time {

        public:
            time(uint64_t __ui64_ts)
                : _ui64_ts(__ui64_ts){}

            std::string to_str() const;
            uint64_t to_ts(bool __b_no_ms = false) const noexcept;
            std::string to_utc_str() const;

        public:
            static time now();
            static int timezone();  // get local time zone (min diff to UTC, e.g. UTC+8 -> 480)

            friend bool operator<(time __lhs, time __rhs);
            friend bool operator<=(time __lhs, time __rhs);
            friend bool operator==(time __lhs, time __rhs);
            friend bool operator>(time __lhs, time __rhs);
            friend bool operator>=(time __lhs, time __rhs);

        private:
            uint64_t _ui64_ts;  // ms based utc timestamp

    }; // class time

    bool operator<(time __lhs, time __rhs);
    bool operator<=(time __lhs, time __rhs);
    bool operator==(time __lhs, time __rhs);
    bool operator>(time __lhs, time __rhs);
    bool operator>=(time __lhs, time __rhs);

} // namespace atina::server::core::utils

#endif // __ATINA_SERVER_CORE_UTILS_TIME_H__
