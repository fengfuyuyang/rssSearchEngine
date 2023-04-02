<?php
/*
 * @Author: fengfuyuyang
 * @Email: fengfuyuyang@outlook.com
 * @Date: 2023-03-26 12:16:31
 * @FilePath: php_client.php
 *
 * Copyright (c) 2023 by fengfuyuyang@outlook.com, All Rights Reserved.
 */

// 从 POST 请求中获取数据并进行过滤
$content = filter_input(INPUT_POST, 'content', FILTER_SANITIZE_STRING);
if (!$content) {
    die("Invalid input data");
}
// 服务端地址和端口
$serverIp = "127.0.0.1";
$serverPort = 8888;
// 创建一个 TCP 套接字
$sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($sock === false) {
    die("socket_create() failed: reason: " . socket_strerror(socket_last_error()));
}
// 设置超时时间
socket_set_option($sock, SOL_SOCKET, SO_RCVTIMEO, array('sec' => 1, 'usec' => 0));
socket_set_option($sock, SOL_SOCKET, SO_SNDTIMEO, array('sec' => 1, 'usec' => 0));
// 连接到 TCP 服务端
$result = socket_connect($sock, $serverIp, $serverPort);
if ($result === false) {
    die("socket_connect() failed: reason: " . socket_strerror(socket_last_error()));
}
// 将数据编码为二进制格式
$content = bin2hex($content);
// 发送数据到 TCP 服务端
if (!socket_write($sock, $content)) {
    die("socket_write() failed: reason: " . socket_strerror(socket_last_error()));
}
// 接收数据，直到数据传输完成
$buffer = "";
try {
    while (true) {
        $len = socket_recv($sock, $buffer, 1024, MSG_WAITALL);
        if ($len === false) {
            die("socket_recv() failed: reason: " . socket_strerror(socket_last_error()));
        }
        if ($len === 0) {
            break;
        }
        echo trim($buffer);
    }
} catch (Exception $e) {
    die("socket_recv() failed: reason: " . $e->getMessage());
}
// 关闭套接字
socket_close($sock);
?>

