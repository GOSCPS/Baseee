# CMakeList.txt: baseee 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

#设置c++版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("baseee" VERSION 0.1.0)

# 将源代码添加到此项目的可执行文件。

# 引入文件
include_directories ("${PROJECT_SOURCE_DIR}/baseee-string")
add_subdirectory (baseee-string) 

include_directories ("${PROJECT_SOURCE_DIR}/baseee-log")
add_subdirectory (baseee-log) 

# 构建可执行文件
add_executable (unit-test "unit-test.cpp" )

# 链接
# target_link_libraries (unit-test baseee-string)
# target_link_libraries (unit-test baseee-log)

# TODO: 如有需要，请添加测试并安装目标。

#安装
# install (TARGETS unit-test DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/string.hpp" 
         DESTINATION include)
install (FILES "${PROJECT_BINARY_DIR}/log.hpp"
         DESTINATION include)
