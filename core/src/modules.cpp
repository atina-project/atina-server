#include"core/modules.h"

#include"core/database/base.h"
#include"Hypodermic/ContainerBuilder.h"

#include"core/module_container.tpp"

using namespace atina::server::core;

void modules::register_modules(Hypodermic::ContainerBuilder* __p__builder) const {
    __p__builder->registerInstance(std::make_shared<database::base>("./test.db"));
    return;
}

template std::shared_ptr<database::base> module_container::resolve();
