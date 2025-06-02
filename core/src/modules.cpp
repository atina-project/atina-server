#include"core/modules.h"

#include<thread>

#include"builtin/database/base.h"
#include"builtin/database/token.h"
#include"builtin/email/email_builder.h"
#include"builtin/email/email_sender.h"
#include"builtin/validation_code.h"
#include"core/config.h"
#include"core/task_scheduler.h"
// #include"core/temp_collector.h"
#include"core/thread_pool.h"
#include"Hypodermic/ContainerBuilder.h"

#include"core/module_container.tpp"

using namespace atina::server::core;

void modules::register_modules(Hypodermic::ContainerBuilder* __p__builder) const {
    __p__builder->registerType<config>().singleInstance();
    __p__builder->registerType<task_scheduler>().singleInstance();
    // __p__builder->registerType<temp_collector>().singleInstance();
    __p__builder->registerInstanceFactory([](Hypodermic::ComponentContext&){
        return std::make_shared<thread_pool>(std::thread::hardware_concurrency());
    }).named("bg_housekeeping_thread_pool").singleInstance();

    __p__builder->registerType<builtin::database::base>().singleInstance();
    __p__builder->registerType<builtin::database::token>().singleInstance();
    __p__builder->registerType<builtin::email::email_builder>().singleInstance();
    __p__builder->registerType<builtin::email::email_sender>().singleInstance();
    __p__builder->registerType<builtin::validation_code>().singleInstance();

    return;
}

INSTANCE_MODULE_CONTAINER_RESOLVE(config);
INSTANCE_MODULE_CONTAINER_RESOLVE(task_scheduler);
// INSTANCE_MODULE_CONTAINER_RESOLVE(temp_collector);
INSTANCE_MODULE_CONTAINER_RESOLVE_NAMED(thread_pool);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::database::base);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::database::token);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::email::email_builder);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::email::email_sender);
INSTANCE_MODULE_CONTAINER_RESOLVE(builtin::validation_code);
