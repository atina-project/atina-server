#include"core/enum.h"

using namespace atina::server;

std::string core::to_string(core::lang __lang){
    switch (__lang)
    {
        case lang::en:   return "en";
        case lang::zhCN: return "zhCN";
    }
}

std::string core::to_string(core::user_type __type){
    switch (__type)
    {
        case user_type::unknown: return "unknown";
        case user_type::admin:   return "admin";
        case user_type::normal:  return "normal";
        case user_type::blocked: return "blocked";
    }
}
