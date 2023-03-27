/**
 * @Author: fengyuyuyang@outlook.com
 * @File Name: config.cpp
 * @File Version: 0.1
 * @Create Time: 2023-03-30 21:38:53
 *
 * Copyright (c) 2023 fengyuyuyang@outlook.com. All rights reserved.
 */

#include "config.h"

namespace ffyy {

bool Config::ParseConfig(const char* config_file_path) {
    pugi::xml_parse_result result = doc_.load_file(config_file_path);
    if (!result) {
        return false;
    }
    return true;
}

std::string Config::GetConfigItem(const std::string &key) {
    return doc_.child("config").child(key.c_str()).child_value();
}

} // namespace ffyy