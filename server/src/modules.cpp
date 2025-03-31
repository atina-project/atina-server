#include"server/modules.h"

#include"Hypodermic/ContainerBuilder.h"
#include"server/server.h"

#include"core/module_container.tpp"

using namespace atina::server::server;

void modules::register_modules(Hypodermic::ContainerBuilder* __p__builder) const {
    __p__builder->registerType<server>();
    return;
}

INSTANCE_MODULE_CONTAINER_RESOLVE(server);
