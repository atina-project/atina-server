#ifndef __ATINA_SERVER_CORE_MODULE_CONTAINER_H__
#define __ATINA_SERVER_CORE_MODULE_CONTAINER_H__

#include<memory>
#include<mutex>
#include<vector>

#include"core/basic_module.h"

namespace Hypodermic {
    class Container; // class Container
} // namespace Hypodermic

namespace atina::server::core {

    class module_container {

        public:
            static void init(const std::vector<basic_module*>& __c_v_modules);
            template<class T>
            static std::shared_ptr<T> resolve();

        private:
            static std::shared_ptr<Hypodermic::Container> _p__container;
            static std::mutex _mtx;

    }; // class module_container

} // namespace atina::server::core

#endif // __ATINA_SERVER_CORE_MODULE_CONTAINER_H__
