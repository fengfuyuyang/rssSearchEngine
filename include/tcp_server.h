/**
 * @Author: fengfuyuyang@outlook.com
 * @File Name: tcp_server.h
 * @File Version: 0.1
 * @Create Time: 2023-04-01 22:58:34
 *
 * Copyright (c) 2023 fengfuyuyang@outlook.com. All rights reserved.
 */

#pragma once

#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "glog/logging.h"

#include "config_parser.h"
#include "thread_pool.h"
namespace ffyy {

class TcpServer {
public:
    TcpServer();
    ~TcpServer();

    /**
     * @brief 初始化服务器
     * @return true 初始化成功
     * @return false 初始化失败
     */
    bool Init();

    /**
     * @brief 启动服务器
     * @return true 启动成功
     * @return false 启动失败
     */
    bool Start();

    /**
     * @brief 停止服务器
     * @return true 停止成功
     * @return false 停止失败
     */
    bool Stop();

    void Test(std::shared_ptr<TcpConnection> conn);

private:
    int listen_fd_; // 监听 socket
    std::string ip_; // IP 地址
    int port_; // 端口号
    bool is_running_; // 服务器是否正在运行
    std::unique_ptr<ThreadPool> thread_pool_; // 线程池
}; // class TcpServer

} // namespace ffyy
