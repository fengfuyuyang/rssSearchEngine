/**
 * @Author: fengfuyuyang@outlook.com
 * @File Name: tcp_server.cpp
 * @File Version: 0.1
 * @Create Time: 2023-04-01 22:57:59
 *
 * Copyright (c) 2023 fengfuyuyang@outlook.com. All rights reserved.
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define MAX_BUFFER_SIZE 1048576

int main(int argc, char const *argv[]) {
    // 创建监听套接字
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0)
    {
        perror("socket error");
        exit(-1);
    }

    // 绑定 IP 和端口号
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind error");
        exit(-1);
    }

    // 开始监听连接请求
    if (listen(listen_fd, 10) < 0) {
        perror("listen error");
        exit(-1);
    }

    while (true) {
        // 接受客户端连接请求
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
        if (conn_fd < 0)
        {
            perror("accept error");
            continue;
        }

        // 接收客户端数据
        char buffer[MAX_BUFFER_SIZE];
        int recv_len = recv(conn_fd, buffer, MAX_BUFFER_SIZE, 0);
        if (recv_len < 0) {
            perror("recv error");
            close(conn_fd);
            continue;
        }

        // 处理客户端数据
        buffer[recv_len] = '\0';
        std::cout << "received data: " << buffer << std::endl;

        // 将处理结果返回给客户端
        std::string response = "server response";
        int send_len = send(conn_fd, response.c_str(), response.length(), 0);
        if (send_len < 0) {
            perror("send error");
            close(conn_fd);
            continue;
        }

        // 关闭连接
        close(conn_fd);
    }

    // 关闭监听套接字
    close(listen_fd);

    return 0;
}
