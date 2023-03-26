<?php
/*
 * @Author: fengfuyuyang
 * @Email: fengfuyuyang@outlook.com
 * @Date: 2023-03-26 12:16:31
 * @FilePath: php_client.php
 *
 * Copyright (c) 2023 by fengfuyuyang@outlook.com, All Rights Reserved.
 */

// 定义服务端IP和端口号
$host = '127.0.0.1';
$port = 8888;

/**
 * 与服务端建立连接
 *
 * @param $host
 * @param $port
 * @param int $timeout 超时时间
 * @return false|resource
 * @throws Exception
 */
function connectToServer($host, $port, $timeout = 30)
{
    // 创建套接字
    $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
    if (!$socket) {
        throw new Exception("创建套接字失败", socket_last_error());
    }

    // 设定超时时间
    socket_set_option($socket, SOL_SOCKET, SO_RCVTIMEO, ['sec' => $timeout, 'usec' => 0]);

    // 是否阻塞模式
    if (!socket_set_nonblock($socket)) {
        throw new Exception("设置非阻塞模式失败", socket_last_error());
    }

    // 连接服务端
    $result = socket_connect($socket, $host, $port);
    if (!$result && socket_last_error() !== SOCKET_EINPROGRESS) {
        throw new Exception("连接服务端失败", socket_last_error());
    }

    return $socket;
}

/**
 * 发送数据
 *
 * @param $socket
 * @param $data
 * @return string
 * @throws Exception
 */
function sendToServer($socket, $data)
{
    // 获取数据长度
    $dataLength = strlen($data);

    // 数据长度大于1M时，抛出异常
    if ($dataLength > 1048576) {
        throw new Exception("发送数据长度过长", -1);
    }

    // 打包数据长度，并发送数据
    $packedDataLength = pack('N', $dataLength);
    $sent = socket_write($socket, $packedDataLength . $data, $dataLength + 4);
    if (!$sent || $sent !== $dataLength + 4) {
        throw new Exception("发送数据失败", socket_last_error());
    }

    // 接收服务端返回的数据
    $buffer = '';
    $lengthLeft = $dataLength;
    while (true) {
        $receiveData = '';
        $receivedLength = socket_recv($socket, $receiveData, $lengthLeft, MSG_WAITALL);
        if (!$receivedLength || $receiveData === '') {
            break;
        }
        $buffer .= $receiveData;
        $lengthLeft -= $receivedLength;
        if ($lengthLeft === 0) {
            break;
        }
    }

    // 返回结果
    return $buffer;
}

// 使用示例
try {
    // 与服务端建立连接
    $socket = connectToServer($host, $port);

    // 发送数据，接收服务端返回的数据
    $data = 'hello world';
    $result = sendToServer($socket, $data);
    echo 'received data: ' . $result . PHP_EOL;

    // 可以多次发送数据
    $data2 = 'test data';
    $result2 = sendToServer($socket, $data2);
    echo 'received data2: ' . $result2 . PHP_EOL;

    // 关闭套接字
    socket_close($socket);
} catch (Exception $e) {
    echo 'Error: ' . $e->getMessage() . PHP_EOL;
}

?>
