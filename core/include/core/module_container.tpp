#include"core/module_container.h"

#include"core/exception/module_exception.h"
#include"Hypodermic/Container.h"

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