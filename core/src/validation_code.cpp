#include"builtin/validation_code.h"

#include<random>

#include"core/utils/string.h"
#include"core/utils/time.h"
#include"core/utils/uuid.h"

using namespace atina::server::core::builtin;

validation_code::validation_code(std::shared_ptr<config> __p__config){
    if (__p__config->validation_code_style() == 0)
    {
        this->_s_charpool = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }
    else
    {
        this->_s_charpool = "0123456789";
    }
    this->_ui_valid_time_length_ms = __p__config->validation_code_valid_time_length_min() * 60 * 1000;
    return;
}

bool validation_code::check_validation_code(const std::string& __c_s_token, const std::string& __c_s_code){
    std::lock_guard<std::mutex> lock(this->_mtx);

    std::string code = __c_s_code;
    utils::string::to_upper(code);
    // ignore cases 

    auto it = this->_codes.find(__c_s_token);
    if (it == this->_codes.end())
    {
        return false;
    } // token doesn't exist
    else if (it->second.s_code != code)
    {
        return false;
    } // wrong code
    else if (it->second.ui64_expire_time < utils::time::now().to_ts())
    {
        return false;
    } // expired

    this->_codes.erase(it);
    // once used, this validation code will be deleted
    return true;
}

validation_code::code validation_code::get_new_validation_code(int __i_size){
    __i_size = (__i_size < this->_c_i_validation_code_min_size) ? this->_c_i_validation_code_min_size
                                                                : __i_size;
    __i_size = (__i_size > this->_c_i_validation_code_max_size) ? this->_c_i_validation_code_max_size
                                                                : __i_size;
    // make sure size is in range
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> distribution(0, this->_s_charpool.size() - 1);
    
    code code = {};
    code.s_token = utils::uuid::generate();
    for (int i = 0 ; i < __i_size ; i++)
    {
        code.s_code += this->_s_charpool[distribution(generator)];
    }
    code.ui64_expire_time = utils::time::now().to_ts() + this->_ui_valid_time_length_ms;

    std::lock_guard<std::mutex> lock(this->_mtx);
    this->_codes[code.s_token] = {code.s_code, code.ui64_expire_time};

    return code;
}
