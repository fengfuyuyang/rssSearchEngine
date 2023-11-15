/**
 * @Author: fengfuyuyang@outlook.com
 * @File Name: task_queue.h
 * @File Version: 0.1
 * @Create Time: 2023-04-05 16:52:16
 *
 * Copyright (c) 2023 fengfuyuyang@outlook.com. All rights reserved.
 */

#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "tcp_connection.h"

namespace ffyy {
class TaskQueue {
public:
    using Task = std::function<void(std::shared_ptr<TcpConnection>)>;

    TaskQueue() = default;

    void Push(Task task) {
        std::unique_lock<std::mutex> lock(mutex_);
        tasks_.push(std::move(task));
        cv_.notify_one();
    }

    Task Pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] {
            return !tasks_.empty();
        });
        auto task = std::move(tasks_.front());
        tasks_.pop();
        return task;
    }

    void Run(std::shared_ptr<TcpConnection> conn) {
        conn->Start();
    }

private:
    std::queue<Task> tasks_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

} // namespace ffyy

// class TaskQueue {
// public:
//     explicit TaskQueue(int conn_fd) : conn_fd_(conn_fd) {}

//     void operator()() {
//         // 接收客户端发送的数据
//         char buffer[1024] = {0};
//         int length = recv(conn_fd_, buffer, sizeof(buffer), 0);
//         if (length == -1) {
//             LOG(ERROR) << "Receive data failed. " << strerror(errno);
//             close(conn_fd_);
//             return;
//         }

//         LOG(INFO) << "Receive data: " << buffer;

//         // 创建 JSON 对象
//         Json::Value root;
//         root["name"] = "Alice";
//         root["age"] = 20;

//         // 将 JSON 对象转换成字符串
//         Json::StreamWriterBuilder builder;
//         builder["indentation"] = "";
//         std::string jsonString = Json::writeString(builder, root);

//         // 发送数据给客户端
//         if (send(conn_fd_, jsonString.c_str(), jsonString.size(), 0) == -1) {
//             LOG(ERROR) << "Send data failed. " << strerror(errno);
//         }

//         LOG(INFO) << "Send data: " << jsonString;

//         close(conn_fd_);
//     }

// private:
//     int conn_fd_;
// };

// #pragma once

// #include <queue>
// #include <mutex>
// #include <condition_variable>
// #include <functional>
// #include <memory>
// #include "tcp_connection.h"

// class TaskQueue {
// public:
//     explicit TaskQueue(std::shared_ptr<TcpServer> server_ptr)
//         : server_ptr_(server_ptr) {}

//     void AddTask(TcpConnection conn) {
//         Task task(std::move(conn));
//         std::lock_guard<std::mutex> lock(mutex_);
//         tasks_.push(std::move(task));
//     }

//     void Run() {
//         while (true) {
//             Task task;
//             {
//                 std::lock_guard<std::mutex> lock(mutex_);
//                 if (!tasks_.empty()) {
//                     task = std::move(tasks_.front());
//                     tasks_.pop();
//                 }
//             }

//             if (task) {
//                 task(server_ptr_);
//             }
//         }
//     }

// private:
//     using Task = std::function<void(std::shared_ptr<TcpConnect>)>;

//     std::shared_ptr<TcpServer> server_ptr_;
//     std::queue<Task> tasks_;
//     std::mutex mutex_;
// };


