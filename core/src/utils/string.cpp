#include"core/utils/string.h"

#include<algorithm>

using namespace atina::server::core::utils;

std::string string::to_upper(std::string& __r_s_str){
    std::transform(__r_s_str.begin(), __r_s_str.end(), __r_s_str.begin(), ::toupper);
    return __r_s_str;
}

std::string string::to_lower(std::string& __r_s_str){
    std::transform(__r_s_str.begin(), __r_s_str.end(), __r_s_str.begin(), ::tolower);
    return __r_s_str;
}
