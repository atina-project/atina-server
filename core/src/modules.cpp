#include"core/modules.h"

#include"builtin/database/base.h"
#include"builtin/database/token.h"
#include"builtin/email/email_builder.h"
#include"builtin/email/email_sender.h"
#include"core/config.h"
#include"Hypodermic/ContainerBuilder.h"

#include"core/module_container.tpp"

using namespace atina::server::core;

void modules::register_modules(Hypodermic::ContainerBuilder* __p__builder) const {
    __p__builder->registerType<config>();

    __p__builder->registerType<builtin::database::base>();
    __p__builder->registerType<builtin::database::token>();
    __p__builder->registerType<builtin::email::email_builder>();
    __p__builder->registerType<builtin::email::email_sender>();

    return;
}

INSTANCE_MODULE_CONTAINER_RESOLVE(config);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::database::base);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::database::token);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::email::email_builder);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::email::email_sender);
