#include"core/module_container.h"

#include"Hypodermic/ContainerBuilder.h"
#include"Hypodermic/Container.h"

using namespace atina::server::core;

void module_container::init(const std::vector<basic_module*>& __c_v_modules){
    std::lock_guard<std::mutex> lock(_mtx);
    Hypodermic::ContainerBuilder builder;
    for (const auto& it : __c_v_modules)
    {
        it->register_modules(&builder);
    }
    _p__container = builder.build();
    return;
}

std::shared_ptr<Hypodermic::Container> module_container::_p__container;
std::mutex module_container::_mtx;
