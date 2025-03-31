#ifndef __ATINA_SERVER_SERVER_MODULES_H__
#define __ATINA_SERVER_SERVER_MODULES_H__

#include"core/basic_module.h"

namespace atina::server::server {

    class modules final : public core::basic_module {

        public:
            modules(){}
            virtual ~modules(){}

            void register_modules(Hypodermic::ContainerBuilder* __p__builder) const override;

    }; // class module

} // namespace atina::server::server

#endif // __ATINA_SERVER_SERVER_MODULES_H__
