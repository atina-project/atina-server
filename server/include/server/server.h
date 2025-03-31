#ifndef __ATINA_SERVER_SERVER_SERVER_H__
#define __ATINA_SERVER_SERVER_SERVER_H__

#include<string>

namespace atina::server::server {

    class server {

        public:
            server(){}
            ~server(){}

        public:
            std::string api_hi() const;

    }; // class server

} // namespace atina::server::server

#endif // __ATINA_SERVER_SERVER_SERVER_H__
