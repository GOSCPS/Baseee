cmake_minimum_required (VERSION 3.8)

#设置c++版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("baseee-log" VERSION 0.1.0)

#构建
add_library(baseee-log "log.hpp" "log.cpp" )

#安装
install (TARGETS baseee-log DESTINATION bin)
install (FILES "log.hpp" DESTINATION include)