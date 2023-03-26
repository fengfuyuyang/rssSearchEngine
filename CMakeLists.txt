cmake_minimum_required(VERSION 3.0.0)

# 项目名
project(rssSearchEngine VERSION 0.1.0)

# 指定头文件目录
include_directories(inc)

# 查照src目录下所有源文件
# 将所有源文件名称保存到'DIR_SRC'变量
aux_source_directory(src DIR_SRCS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -g -pthread")

# 添加c++11编译选项
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if (COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

# 设置release版可执行程序输出目录
set(bin_release ${CMAKE_SOURCE_DIR}/bin/release)

# 设置debug版可执行程序输出目录
set(bin_debug ${CMAKE_SOURCE_DIR}/bin/debug)

# 指定release版可执行程序输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${bin_release})

# 指定debug版可执行程序输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${bin_debug})

# 指定生成目标
add_executable(demo ${DIR_SRCS})
