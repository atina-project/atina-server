#ifndef __ATINA_SERVER_CORE_MODULES_H__
#define __ATINA_SERVER_CORE_MODULES_H__

#include"core/basic_module.h"

namespace atina::server::core {

    class modules final : public basic_module {

        public:
            modules(){}
            virtual ~modules(){}

            void register_modules(Hypodermic::ContainerBuilder* __p__builder) const override;

    }; // class modules

} // namespace atina::server::core

#endif // __ATINA_SERVER_CORE_MODULES_H__
