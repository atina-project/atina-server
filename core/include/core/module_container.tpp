#include"core/module_container.h"

#include"core/exception/module_exception.h"
#include"Hypodermic/Container.h"

#define INSTANCE_MODULE_CONTAINER_RESOLVE(type)                                         \
    template std::shared_ptr<type> atina::server::core::module_container::resolve()

#define INSTANCE_MODULE_CONTAINER_RESOLVE_NAMED(type)                                   \
    template std::shared_ptr<type> atina::server::core::module_container::resolve_named(const std::string& __c_s_name)

using namespace atina::server::core;

template<class T>
std::shared_ptr<T> module_container::resolve(){
    std::lock_guard<std::mutex> lock(_mtx);
    if (_p__container == nullptr)
    {
        throw exception::module_exception(
            exception::module_errcode::MODULE_NOT_INITED,
            "module container not initialized"
        );
    }
    return _p__container->resolve<T>();
}

template<class T>
std::shared_ptr<T> module_container::resolve_named(const std::string& __c_s_name){
    std::lock_guard<std::mutex> lock(_mtx);
    if (_p__container == nullptr)
    {
        throw exception::module_exception(
            exception::module_errcode::MODULE_NOT_INITED,
            "module container not initialized"
        );
    }
    return _p__container->resolveNamed<T>(__c_s_name);
}
