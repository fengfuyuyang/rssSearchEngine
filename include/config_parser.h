/**
 * @Author: fengfuyuyang@outlook.com
 * @File Name: config_parser.h
 * @File Version: 0.1
 * @Create Time: 2023-03-30 21:35:40
 *
 * Copyright (c) 2023 fengyuyuyang@outlook.com. All rights reserved.
 */

#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

#include <string>
#include "pugixml.hpp"

namespace ffyy {

// 配置文件解析类
class ConfigParser {
public:
    ConfigParser(const std::string& filename);
    ~ConfigParser() {
    }

    /**
     * @brief 从配置文件中读取 IP 地址
     * @return std::string IP 地址
     */
    std::string GetIp() const;

    /**
     * @brief 从配置文件中读取端口号
     * @return int 端口号
     */
    int GetPort() const;

    /**
     * @brief 从配置文件中读取线程池大小
     * @return int 线程池大小
     */
    int GetThreadPoolSize() const;

    /**
     * @brief 从配置文件中读取线程池队列大小
     * @return int 线程池队列大小
     */
    int GetThreadPoolQueueSize() const;

private:
    /**
     * @brief pugixml的文档对象
     */
    pugi::xml_document doc_;
}; // class Config
} // namespace ffyy

#endif // INCLUDE_CONFIG_H_