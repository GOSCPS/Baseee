﻿# CMakeList.txt: baseee 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

#设置c++版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("baseee" VERSION 0.1.0)

# 将源代码添加到此项目的可执行文件。

# Python
#find_package(Python3 COMPONENTS Development)
#find_package(PythonLibs 3 REQUIRED)
#include_directories(${Python3_INCLUDE_DIRS})

# 引入文件
include_directories ("${PROJECT_SOURCE_DIR}/src/")

add_subdirectory (src/baseee-string) 

add_subdirectory (src/baseee-log) 

# 构建可执行文件
add_executable (unit-test "unit-test.cpp")

# 链接
# target_link_libraries (unit-test baseee-string)
# target_link_libraries (unit-test baseee-log)
# target_link_libraries (unit-test baseee-python)
#TARGET_LINK_LIBRARIES(unit-test ${PYTHON_LIBRARIES})


# TODO: 如有需要，请添加测试并安装目标。

#安装
# install (TARGETS unit-test DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/src/string.hpp" 
         DESTINATION include)
install (FILES "${PROJECT_BINARY_DIR}/src/log.hpp"
         DESTINATION include)