/**
 * @Author: fengfuyuyang@outlook.com
 * @File Name: thread_pool.cpp
 * @File Version: 0.1
 * @Create Time: 2023-04-05 15:53:29
 *
 * Copyright (c) 2023 fengfuyuyang@outlook.com. All rights reserved.
 */

#include "thread_pool.h"

namespace ffyy {

ThreadPool::~ThreadPool() {
    if (running_.load()) {
        Stop();
    }
}

void ThreadPool::Start() {
    running_.store(true);
    for (size_t i = 0; i < thread_count_; ++i) {
        threads_.emplace_back(&ThreadPool::ThreadFunc, this);
    }
}

void ThreadPool::Stop() {
    running_.store(false);
    cv_.notify_all();
    for (auto& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    threads_.clear();
}

void ThreadPool::AddTask(TaskQueue::Task task) {
    task_queue_.Push(std::move(task));
}

void ThreadPool::ThreadFunc() {
    while (running_.load()) {
        auto task = task_queue_.Pop();
        task();
    }
}

} // namespace ffyy