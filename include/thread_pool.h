#include <thread>
#include <vector>
#include <atomic>
#include <iostream>
#include "task_queue.h"

class ThreadPool {
public:
    ThreadPool() = default;

    explicit ThreadPool(size_t thread_count) : thread_count_(thread_count) {}

    ~ThreadPool() {
        if (running_.load()) {
            Stop();
        }
    }

    void Start() {
        running_.store(true);
        for (size_t i = 0; i < thread_count_; ++i) {
            threads_.emplace_back(&ThreadPool::ThreadFunc, this);
        }
    }

    void Stop() {
        running_.store(false);
        cv_.notify_all();
        for (auto& thread : threads_) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        threads_.clear();
    }

    void AddTask(TaskQueue::Task task) {
        task_queue_.Push(std::move(task));
    }

    void ThreadFunc() {
        while (running_.load()) {
            auto task = task_queue_.Pop();
            task();
        }
    }

private:
    size_t thread_count_ = std::thread::hardware_concurrency();
    std::atomic_bool running_ {false};
    TaskQueue task_queue_;
    std::vector<std::thread> threads_;
    std::mutex mutex_;
    std::condition_variable cv_;
};
