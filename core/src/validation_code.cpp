#include"builtin/validation_code.h"

#include<random>

#include"core/utils/string.h"
#include"core/utils/time.h"
#include"core/utils/uuid.h"
#include"g3log/g3log.hpp"

using namespace atina::server::core::builtin;

validation_code::validation_code(std::shared_ptr<config> __p__config, std::shared_ptr<task_scheduler> __p__scheduler)
    : _p__scheduler(__p__scheduler)
{
    if (__p__config->validation_code_style() == 0)
    {
        this->_s_charpool = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        LOG(INFO) << "Using upper letter + number charpool.";
    }
    else
    {
        this->_s_charpool = "0123456789";
        LOG(INFO) << "Using number only charpool.";
    }
    this->_ui_valid_time_length_ms = __p__config->validation_code_valid_time_length_min() * 60 * 1000;
    this->_i_bg_task_token = this->_p__scheduler->add_task(
        "validation_code_cleanup",
        [this](){ this->_cleanup(); },
        this->_c_ui_auto_cleanup_interval_min
    );
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
        LOG(INFO) << "Failed to verify validation code, token doesn't exist. [token=\"" << __c_s_token << "\"]";
        return false;
    } // token doesn't exist
    else if (it->second.s_code != code)
    {
        LOG(INFO) << "Failed to verify validation code, unmatched code. [token=\"" << __c_s_token << "\"]";
        return false;
    } // wrong code
    else if (it->second.ui64_expire_time < utils::time::now().to_ts())
    {
        LOG(INFO) << "Failed to verify validation code, expired code. [token=\"" << __c_s_token << "\",expired_at=" << it->second.ui64_expire_time << "]";
        return false;
    } // expired

    this->_codes.erase(it);
    LOG(INFO) << "Validation code verified, code deleted. [token=\"" << __c_s_token << "\"]";
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

    LOG(INFO) << "New validation code added. [token=\"" << code.s_token << "\",expires_at=" << code.ui64_expire_time << "]";
    return code;
}

void validation_code::_cleanup(){
    std::lock_guard<std::mutex> lock(this->_mtx);

    uint64_t now_ts = utils::time::now().to_ts();
    size_t old_size = this->_codes.size();
    for (auto it = this->_codes.begin() ; it != this->_codes.end() ; )
    {
        if (it->second.ui64_expire_time < now_ts)
        {
            it = this->_codes.erase(it);
        }
        else
        {
            ++it;
        }
    }
    size_t new_size = this->_codes.size();
    LOG(INFO) << "Validation code cleanup finished. [expired_codes_num=" << old_size - new_size << "]";

    return;
}
