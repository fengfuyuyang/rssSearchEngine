/**
 * @Author: fengfuyuyang@outlook.com
 * @File Name: thread_pool.h
 * @File Version: 0.1
 * @Create Time: 2023-04-05 15:53:13
 *
 * Copyright (c) 2023 fengfuyuyang@outlook.com. All rights reserved.
 */

#pragma once

#include <thread>
#include <vector>
#include <atomic>
#include <iostream>
#include "task_queue.h"

namespace ffyy {
class ThreadPool {
public:
    ThreadPool() = default;

    explicit ThreadPool(size_t thread_count) : thread_count_(std::max<size_t>(1, thread_count)) {
    }

    ~ThreadPool();

    /**
     * @brief 启动线程池
     */
    void Start();

    /**
     * @brief 停止线程池
     */
    void Stop();

    /**
     * @brief 向线程池中添加任务
     * @param task 任务
     */
    void AddTask(TaskQueue::Task task);

private:
    /**
     * @brief 线程函数
     */
    void ThreadFunc();

private:
    size_t thread_count_;
    std::atomic_bool running_ {false};
    TaskQueue task_queue_;
    std::vector<std::thread> threads_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

} // namespace ffyy