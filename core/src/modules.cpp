#include"core/modules.h"

#include"builtin/database/base.h"
#include"core/config.h"
#include"Hypodermic/ContainerBuilder.h"

#include"core/module_container.tpp"

using namespace atina::server::core;

void modules::register_modules(Hypodermic::ContainerBuilder* __p__builder) const {
    __p__builder->registerType<config>();

    __p__builder->registerInstance(std::make_shared<builtin::database::base>("./test.db"));
    return;
}

template std::shared_ptr<config> module_container::resolve();
template std::shared_ptr<builtin::database::base> module_container::resolve();
