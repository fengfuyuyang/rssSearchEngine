cmake_minimum_required(VERSION 3.0.0)

# 项目名
project(rssSearchEngine VERSION 0.1.0)

# 指定头文件目录
include_directories(include)

# 查找 src 目录下所有源文件
# 将所有源文件名称保存到 'DIR_SRCS' 变量
aux_source_directory(src DIR_SRCS)

# 添加编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -g -pthread -std=c++11")

# 设置可执行程序输出目录
set(bin_dir ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${bin_dir}/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${bin_dir}/debug)

# 指定生成目标
add_executable(rssSearchEngine ${DIR_SRCS})

# 设置cmake module的路径
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_module/")

# 添加glog库
find_package(GLOG REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS})
target_link_libraries(rssSearchEngine ${GLOG_LIBRARIES})

# 添加pugixml库
find_package(PUGIXML REQUIRED)
include_directories(${PUGIXML_INCLUDE_DIRS})
target_link_libraries(rssSearchEngine ${PUGIXML_LIBRARIES})

# 添加jsoncpp库
find_package(JSONCPP REQUIRED)
include_directories(${JSONCPP_INCLUDE_DIRS})
target_link_libraries(rssSearchEngine ${JSONCPP_LIBRARIES})

# 添加cppjieba库
set(LIMONP_VERSION "v0.6.6")
set(CPPJIEBA_VERSION "v5.1.0")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/limonp-${LIMONP_VERSION}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/cppjieba-${CPPJIEBA_VERSION}/include)