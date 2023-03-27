###
 # @Author: fengfuyuyang@outlook.com
 # @File Name: config.h
 # @File Version: 0.1
 # @Create Time: 2023-03-27 20:25:05
 #
 # Copyright (c) 2023 fengfuyuyang@outlook.com. All rights reserved.
###

#!/bin/bash

# 指定所需库版本号
GLOG_VERSION=v0.6.0
PUGIXML_VERSION=v1.13
JSONCPP_VERSION=1.9.5
LIMONP_VERSION=v0.6.6
CPPJIEBA_VERSION=v5.1.0

HOME=`pwd`

# 将 GLOG_VERSION 设置到 FindGLOG.cmake 中
sed -i "/set(GLOG_VERSION/c set(GLOG_VERSION $GLOG_VERSION)" ${HOME}/cmake_module/FindGLOG.cmake

# 将 PUGIXML_VERSION 设置到 FindPUGIXML.cmake 中
sed -i "/set(PUGIXML_VERSION/c set(PUGIXML_VERSION $PUGIXML_VERSION)" ${HOME}/cmake_module/FindPUGIXML.cmake

# 将 JSONCPP_VERSION 设置到 FindJSONCPP.cmake 中
sed -i "/set(JSONCPP_VERSION/c set(JSONCPP_VERSION $JSONCPP_VERSION)" ${HOME}/cmake_module/FindJSONCPP.cmake

# 将 LIMONP_VERSION 设置到 CMakeLists.txt 中
sed -i "/set(LIMONP_VERSION/c set(LIMONP_VERSION \"$LIMONP_VERSION\")" CMakeLists.txt

# 将 CPPJIEBA_VERSION 设置到 CMakeLists.txt 中
sed -i "/set(CPPJIEBA_VERSION/c set(CPPJIEBA_VERSION \"$CPPJIEBA_VERSION\")" CMakeLists.txt

cd ${HOME}/thirdparty

# 安装 glog 库
if [ -e glog-${GLOG_VERSION} ]
then
    echo "glog-${GLOG_VERSION} already installed."
else
    git clone --depth=10 --branch ${GLOG_VERSION} https://github.com/google/glog.git glog-${GLOG_VERSION}
    cd glog-${GLOG_VERSION}
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=. ..
    make
    make install
    cd ${HOME}/thirdparty
fi


# 安装 pugixml 库
if [ -e pugixml-${PUGIXML_VERSION} ]
then
    echo "pugixml-${PUGIXML_VERSION} already installed."
else
    git clone --depth=10 --branch ${PUGIXML_VERSION} https://github.com/zeux/pugixml.git pugixml-${PUGIXML_VERSION}
    cd pugixml-${PUGIXML_VERSION}
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=. ..
    make
    make install
    cd ${HOME}/thirdparty
fi

# 安装 jsoncpp 库
if [ -e jsoncpp-${JSONCPP_VERSION} ]
then
    echo "jsoncpp-${JSONCPP_VERSION} already installed."
else
    git clone --depth=10 --branch ${JSONCPP_VERSION} https://github.com/open-source-parsers/jsoncpp.git jsoncpp-${JSONCPP_VERSION}
    cd jsoncpp-${JSONCPP_VERSION}
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=. ..
    make
    make install
    cd ${HOME}/thirdparty
fi

# 安装 limonp 库
if [ -e limonp-${LIMONP_VERSION} ]
then
    echo "limonp-${LIMONP_VERSION} already installed."
else
    git clone --depth=10 --branch ${LIMONP_VERSION} https://github.com/yanyiwu/limonp.git limonp-${LIMONP_VERSION}
fi


# 安装 cppjieba 库
if [ -e cppjieba-${CPPJIEBA_VERSION} ]
then
    echo "cppjieba-${CPPJIEBA_VERSION} already installed."
else
    git clone --depth=10 --branch ${CPPJIEBA_VERSION} https://github.com/yanyiwu/cppjieba.git cppjieba-${CPPJIEBA_VERSION}
fi

cd ${HOME}
