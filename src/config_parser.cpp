/**
 * @Author: fengyuyuyang@outlook.com
 * @File Name: config.cpp
 * @File Version: 0.1
 * @Create Time: 2023-03-30 21:38:53
 *
 * Copyright (c) 2023 fengyuyuyang@outlook.com. All rights reserved.
 */

#include "config_parser.h"

namespace ffyy {

ConfigParser::ConfigParser(const std::string& filename) {
    pugi::xml_parse_result result = doc_.load_file(filename.c_str());
    if (!result) {
        throw std::runtime_error("Error parsing XML: " + std::string(result.description()));
    }
}

std::string ConfigParser::GetIp() const {
    return doc_.child("config").child_value("ip");
}

int ConfigParser::GetPort() const {
    return doc_.child("config").child("port").text().as_int();
}

int ConfigParser::GetThreadPoolSize() const {
    return doc_.child("config").child("threadPool").child("size").text().as_int();
}

int ConfigParser::GetThreadPoolQueueSize() const {
    return doc_.child("config").child("threadPool").child("queueSize").text().as_int();
}

} // namespace ffyy