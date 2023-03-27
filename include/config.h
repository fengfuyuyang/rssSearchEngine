/**
 * @Author: fengfuyuyang@outlook.com
 * @File Name: config.h
 * @File Version: 0.1
 * @Create Time: 2023-03-30 21:35:40
 *
 * Copyright (c) 2023 fengyuyuyang@outlook.com. All rights reserved.
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include <string>
#include "pugixml.hpp"

namespace ffyy {

// 配置文件解析类
class Config {
public:
    Config () : doc_() {
    }
    ~Config() {
    }

    /**
     * @brief 解析配置文件
     * @param config_file_path 配置文件路径
     * @return true 解析成功
     * @return false 解析失败
     */
    bool ParseConfig(const char* config_file_path);

    /**
     * @brief 获取配置项
     * @param key 配置项的键
     * @return std::string 配置项的值
     */
    std::string GetConfigItem(const std::string &key);

private:
    /**
     * @brief pugixml的文档对象
     */
    pugi::xml_document doc_;
}; // class Config
} // namespace ffyy

#endif // INC_CONFIG_H_