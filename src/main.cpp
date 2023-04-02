/**
 * @Author: fengfuyuyang@outlook.com
 * @File Name: main.cpp
 * @File Version: 0.1
 * @Create Time: 2023-03-30 22:03:00
 *
 * Copyright (c) 2023 fengfuyuyang@outlook.com. All rights reserved.
 */

#include <iostream>
#include "tcp_server.h"
#include "glog/logging.h"

void Test() {
    ffyy::TcpServer tcp_server;
    if (!tcp_server.Init()) {
        LOG(ERROR) << __FUNCTION__ << " Error: Failed to init tcp server.";
        return;
    }

    if (!tcp_server.Start()) {
        LOG(ERROR) << __FUNCTION__ << " Error: Failed to start tcp server.";
        return;
    }

    if (!tcp_server.Stop()) {
        LOG(ERROR) << __FUNCTION__ << " Error: Failed to stop tcp server.";
        return;
    }
}

int main(int argc, char const *argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir = "../../log";
    FLAGS_logtostderr = false;
    FLAGS_minloglevel = google::INFO;
    FLAGS_max_log_size = 100;
    FLAGS_stop_logging_if_full_disk = true;
    Test();
    return 0;
}