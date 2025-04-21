#include"core/modules.h"

#include"builtin/database/base.h"
#include"builtin/database/token.h"
#include"builtin/email/email_builder.h"
#include"builtin/email/email_sender.h"
#include"builtin/validation_code.h"
#include"core/config.h"
#include"core/task_scheduler.h"
#include"Hypodermic/ContainerBuilder.h"

#include"core/module_container.tpp"

using namespace atina::server::core;

void modules::register_modules(Hypodermic::ContainerBuilder* __p__builder) const {
    __p__builder->registerType<config>();
    __p__builder->registerType<task_scheduler>().singleInstance();

    __p__builder->registerType<builtin::database::base>().singleInstance();
    __p__builder->registerType<builtin::database::token>().singleInstance();
    __p__builder->registerType<builtin::email::email_builder>();
    __p__builder->registerType<builtin::email::email_sender>();
    __p__builder->registerType<builtin::validation_code>().singleInstance();

    return;
}

INSTANCE_MODULE_CONTAINER_RESOLVE(config);
INSTANCE_MODULE_CONTAINER_RESOLVE(task_scheduler);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::database::base);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::database::token);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::email::email_builder);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::email::email_sender);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::validation_code);
