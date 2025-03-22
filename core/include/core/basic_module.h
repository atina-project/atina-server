#ifndef __ATINA_SERVER_CORE_BASIC_MODULE_H__
#define __ATINA_SERVER_CORE_BASIC_MODULE_H__

namespace Hypodermic {
    class ContainerBuilder;
} // namespace Hypodermic

namespace atina::server::core {

    class basic_module {

        public:
            basic_module(){}
            virtual ~basic_module(){}

            virtual void register_modules(Hypodermic::ContainerBuilder* __p__builder) const = 0;

    }; // class basic_module

} // namespace atina::server::core

#endif // __ATINA_SERVER_CORE_BASIC_MODULE_H__
