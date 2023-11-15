#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == -1) {
        std::cerr << "Error: create socket failed." << std::endl;
        return -1;
    }

    // 绑定套接字
    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(8888);
    if (bind(sockfd, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        std::cerr << "Error: bind socket failed." << std::endl;
        close(sockfd);
        return -1;
    }

    // 监听套接字
    if (listen(sockfd, 10) == -1) {
        std::cerr << "Error: listen socket failed." << std::endl;
        close(sockfd);
        return -1;
    }

    // 循环接收客户端连接
    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int connfd = accept(sockfd, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
        if (connfd == -1) {
            std::cerr << "Error: accept socket failed." << std::endl;
            continue;
        }

        // 接收客户端发送的数据
        char buffer[1024] = {0};
        int length = recv(connfd, buffer, sizeof(buffer), 0);
        if (length == -1) {
            std::cerr << "Error: receive data failed." << std::endl;
            close(connfd);
            continue;
        }

        // 打印接收到的数据
        std::cout << "Receive data from client: " << buffer << std::endl;

        // 发送数据给客户端
        // if (send(connfd, buffer, length, 0) == -1) {
        //     std::cerr << "Error: send data failed." << std::endl;
        // }

        // 关闭连接
        close(connfd);
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}


void foo(int x) {
    std::cout << "foo(" << x << ")" << std::endl;
}

int bar(int y) {
    return y * 2;
}

int main() {
    ThreadPool pool(4); // 创建一个线程池，包含 4 个线程

    // 添加任务到线程池中
    pool.AddTask([](){
        std::cout << "Hello" << std::endl;
    });
    pool.AddTask(std::bind(foo, 42));
    pool.AddTask(std::bind(bar, 3));

    // 等待一段时间，让任务在后台线程执行
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 停止线程池，并等待所有线程完成
    pool.Stop();

    return 0;
}


class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
public:
    TcpConnection(int sockfd) : sockfd_(sockfd) {}
    void Start() {}
private:
    int sockfd_;
};
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

class ThreadPool {
public:
    ThreadPool() : ThreadPool(std::thread::hardware_concurrency()) {}

    explicit ThreadPool(size_t thread_count) :
        thread_count_(std::max<size_t>(1, thread_count)) {}

    ~ThreadPool() {
        Stop();
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
        try {
            while (running_.load()) {
                auto task = task_queue_.Pop();
                task(n);
            }
        } catch (...) {
            std::cout << "Exception caught in ThreadPool::ThreadFunc" << std::endl;
        }
    }

private:
    size_t thread_count_;
    std::atomic_bool running_{ false };
    TaskQueue task_queue_;
    std::vector<std::thread> threads_;
    std::mutex mutex_;
    std::condition_variable cv_;
};
