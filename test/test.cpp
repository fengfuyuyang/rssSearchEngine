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
