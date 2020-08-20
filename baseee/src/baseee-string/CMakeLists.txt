cmake_minimum_required (VERSION 3.8)

#设置c++版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("baseee-string" VERSION 0.1.0)

#构建
add_library(baseee-string "string.hpp" "coder.cpp" "string.cpp")

#安装
install (TARGETS baseee-string DESTINATION bin)
install (FILES "string.hpp" DESTINATION include)