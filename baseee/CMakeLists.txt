# CMakeList.txt: baseee 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

#/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
# * IS LICENSED UNDER MIT
# * File:     CMakeLists.txt
# * Content:  Cmake File
# * Copyright (c) 2020 Chhdao All rights reserved.
# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

cmake_minimum_required (VERSION 3.8)

#设置c++版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#构建发布
#SET(CMAKE_BUILD_TYPE "Release")

project ("baseee" VERSION 0.1.0 LANGUAGES CXX)

#设置版本号
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)


# 让Windows安全函数爬
if(WIN32)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

#configure_file(config.h.in config.h)

#构建模块
set(BaseeeString ${PROJECT_SOURCE_DIR}/src/baseee-string)

set(BaseeeLog ${PROJECT_SOURCE_DIR}/src/baseee-log)

set(BaseeeParser ${PROJECT_SOURCE_DIR}/src/baseee-parser)

set(BaseeeComponents ${PROJECT_SOURCE_DIR}/src/baseee-components)

set(BaseeeTest ${PROJECT_SOURCE_DIR}/src/baseee-test)

set(BaseeeModule ${BaseeeString} ${BaseeeLog} ${BaseeeParser} ${BaseeeComponents} ${BaseeeTest})

add_library(baseee STATIC 
${BaseeeParser}/inip.cpp 
${BaseeeParser}/jsonp.cpp 
${BaseeeParser}/jsonb.cpp
${BaseeeLog}/log.cpp 
${BaseeeString}/string.cpp 
)

#构建单元测试
aux_source_directory(. ALL_SOURCE_FILE)
add_executable(unit-test 
${ALL_SOURCE_FILE}
)

target_include_directories(unit-test PRIVATE ${BaseeeModule})

target_link_libraries(unit-test baseee)

#安装
install(TARGETS 
baseee
EXPORT BaseeeLib
LIBRARY DESTINATION lib  # 动态库安装路径
ARCHIVE DESTINATION lib  # 静态库安装路径
RUNTIME DESTINATION bin  # 可执行文件安装路径
PUBLIC_HEADER DESTINATION include  # 头文件安装路径
)

#安装头文件
install(FILES 
${BaseeeLog}/log.hpp
${BaseeeString}/string.hpp
${BaseeeParser}/inip.hpp
${BaseeeParser}/jsonp.hpp
${BaseeeComponents}/global.hpp
DESTINATION include/baseee
)

#安装cmake包
install(
  EXPORT BaseeeLib
  FILE BaseeeLibTargets.cmake
  NAMESPACE baseee::
  DESTINATION share/baseee)

include(CMakePackageConfigHelpers)

set(BASEEE_INCLUDE_DIRS DESTINATION  ${CMAKE_INSTALL_PREFIX}/include)
set(BASEEE_LIB_DIR DESTINATION  ${CMAKE_INSTALL_PREFIX}/lib)

configure_package_config_file(
  BaseeeConfig.cmake.in
  ${PROJECT_BINARY_DIR}/BaseeeConfig.cmake
  INSTALL_DESTINATION share/baseee)

 write_basic_package_version_file(
  BaseeeConfigVersion.cmake
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY SameMajorVersion)

  install(FILES "${PROJECT_BINARY_DIR}/BaseeeConfig.cmake"
              "${PROJECT_BINARY_DIR}/BaseeeConfigVersion.cmake"
        DESTINATION share/baseee)

#打包
#set(CPACK_PACKAGE_VENDOR ${PROJECT_NAME})
#
# 设置版本
#set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
#set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
#set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
#set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
#
#打包文件
#set(CPACK_PACKAGE_DIRECTORY ${PROJECT_SOURCE_DIR}/pack)
#set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/../LICENSE")
#
#忽略文件
#set(CPACK_SOURCE_IGNORE_FILES
#        ${PROJECT_SOURCE_DIR}/build
#        ${PROJECT_SOURCE_DIR}/pack
#        ${PROJECT_SOURCE_DIR}/.vs)
#        
#
#设置名称
#set(PROJECT_VERSION_FULL ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
#set(CPACK_SOURCE_PACKAGE_FILE_NAME Baseee-${PROJECT_VERSION_FULL})
#
#
# 设置打包类型: tgz 以及 zip 格式
#set(CPACK_GENERATOR "TGZ;ZIP")
#set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
#
#include(CPack)
#
#导出编译目录
#set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
#export(PACKAGE BaseeeLib)