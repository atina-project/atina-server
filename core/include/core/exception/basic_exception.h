#ifndef __ATINA_SERVER_CORE_EXCEPTION_BASIC_EXCEPTION_H__
#define __ATINA_SERVER_CORE_EXCEPTION_BASIC_EXCEPTION_H__

#include<exception>
#include<sstream>
#include<string>

#define ATINA_SERVER_CORE_ADD_NEW_EXCEPTION(ex_name)\
    class ex_name : public atina::server::core::exception::basic_exception<ex_name> {   \
                                                                                        \
        public:                                                                         \
            ex_name(int __i_errcode, const std::string& __c_s_errmsg)                   \
                : basic_exception<ex_name>(__i_errcode, __c_s_errmsg) {}                \
            virtual ~ex_name() noexcept {}                                              \
                                                                                        \
            static constexpr const char* exception_name() noexcept { return #ex_name; } \
                                                                                        \
    };

namespace atina::server::core::exception {

    template<typename T>
    class basic_exception : public std::exception {

        public:
            basic_exception(int __i_errcode, const std::string& __c_s_errmsg)
                : _i_errcode(__i_errcode)
            {
                std::ostringstream oss;
                oss << "[" << T::exception_name() << ":" << this->_i_errcode << "] " << __c_s_errmsg;
                this -> _s_errmsg = oss.str();
                return;
            }
            virtual ~basic_exception() noexcept {}

            int code() const noexcept {
                return this->_i_errcode;
            }
            const char* what() const noexcept override {
                return this->_s_errmsg.c_str();
            }

        private:
            int _i_errcode;
            std::string _s_errmsg;

    }; // class basic_exception

} // namespace atina::server::core::exception

#endif // __ATINA_SERVER_CORE_EXCEPTION_BASIC_EXCEPTION_H__
