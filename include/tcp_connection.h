#pragma once

#include <iostream>
#include <memory>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>
#include <sstream>
#include "json/json.h"

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
public:
    TcpConnection(int sockfd) : sockfd_(sockfd) {}

    void Start() {
        std::string msg = "Hello, world!";
        send(sockfd_, msg.c_str(), msg.size(), 0);

        while (true) {
            char buffer[1024] = {0};
            int length = recv(sockfd_, buffer, sizeof(buffer), 0);
            if (length == -1) {
                std::cerr << "Error: receive data failed." << std::endl;
                break;
            }

            if (length == 0) {
                std::cerr << "Peer closed the connection." << std::endl;
                break;
            }

            std::string request(buffer, length);
            std::cout << "Receive data: " << request << std::endl;

            // 解析 JSON 请求
            Json::CharReaderBuilder builder;
            Json::CharReader *reader = builder.newCharReader();
            Json::Value root;
            std::string errors;
            if (!reader->parse(request.c_str(), request.c_str() + request.size(), &root, &errors)) {
                std::cerr << "Error: Failed to parse JSON request. " << errors << std::endl;
                continue;
            }

            // 处理业务逻辑
            Json::Value response;
            response["result"] = "OK";
            response["data"] = "This is the response data.";

            // 序列化 JSON 响应
            std::ostringstream ss;
            Json::StreamWriterBuilder writerBuilder;
            std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
            writer->write(response, &ss);
            std::string responseString = ss.str();

            // 发送响应数据
            if (send(sockfd_, responseString.c_str(), responseString.size(), 0) == -1) {
                std::cerr << "Error: send data failed." << std::endl;
                break;
            }
            std::cout << "Send data: " << responseString << std::endl;
        }

        close(sockfd_);
    }

private:
    int sockfd_;
};
