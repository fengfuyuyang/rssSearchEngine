/**
 * @Author: fengfuyuyang@outlook.com
 * @File Name: tcp_server.cpp
 * @File Version: 0.1
 * @Create Time: 2023-04-01 23:02:30
 *
 * Copyright (c) 2023 fengfuyuyang@outlook.com. All rights reserved.
 */

#include "tcp_server.h"
#include "task_queue.h"
#include "tcp_connection.h"
#include "log.h"

#include <stdexcept>
#include <cstring>
#include <cerrno>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace ffyy {

TcpServer::TcpServer(uint16_t port, int backlog, int max_thread_num)
    : port_(port),
      backlog_(backlog),
      is_running_(false),
      thread_pool_(new ThreadPool(max_thread_num)) {
}

TcpServer::~TcpServer() {
    Stop();
}

bool TcpServer::Start() {
    if (!is_running_) {
        throw std::runtime_error("Server is not initialized.");
    }

    int optval = 1;
    // 创建套接字
    listen_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd_ < 0) {
        LOG(ERROR) << __FUNCTION__ << " Failed to create socket. " << strerror(errno);
        return false;
    }

    // 设置 SO_REUSEADDR 选项，防止因为 TIME_WAIT 导致 bind 失败
    if (setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        LOG(ERROR) << __FUNCTION__ << " Failed to set SO_REUSEADDR option. " << strerror(errno);
        return false;
    }

    // 绑定地址和端口号
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listen_fd_, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        LOG(ERROR) << __FUNCTION__ << " Failed to bind. " << strerror(errno);
        return false;
    }

    // 监听端口
    if (listen(listen_fd_, backlog_) < 0) {
        LOG(ERROR) << __FUNCTION__ << " Failed to listen. " << strerror(errno);
        return false;
    }

    LOG(INFO) << "Server start successfully.";

    is_running_ = true;

    thread_pool_->Start();

    while (true) {
        // 接受客户端连接请求
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int conn_fd = accept(listen_fd_, (struct sockaddr *)&client_addr, &client_len);

        if (conn_fd < 0) {
            LOG(ERROR) << __FUNCTION__ << " Failed to accept. " << strerror(errno);
            continue;
        }

        // 将连接请求封装成Task对象并添加到TaskQueue中
        TaskQueue::Task task(std::make_shared<TcpConnection>(conn_fd));
        thread_pool_->AddTask(task);
    }

    return true;
}

bool TcpServer::Stop() {
    if (is_running_) {
        is_running_ = false;

        // 关闭套接字
        if (listen_fd_ > 0) {
            close(listen_fd_);
            listen_fd_ = -1;
        }

        thread_pool_->Stop();

        LOG(INFO) << "Server stop successfully.";

        return true;
    }

    return false;
}


}  // namespace ffyy