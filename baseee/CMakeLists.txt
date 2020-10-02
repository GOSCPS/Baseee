# CMakeList.txt: baseee 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

#设置c++版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("baseee" VERSION 0.1.0 LANGUAGES CXX)


# 让Windows安全函数爬
if(WIN32)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

configure_file(config.h.in config.h)

#构建模块
set(BaseeeString ${PROJECT_SOURCE_DIR}/src/baseee-string)
add_library(baseee-string STATIC ${BaseeeString}/string.cpp )

set(BaseeeLog ${PROJECT_SOURCE_DIR}/src/baseee-log)
add_library(baseee-log STATIC ${BaseeeLog}/log.cpp)

#构建单元测试
aux_source_directory(. ALL_SOURCE_FILE)
add_executable(unit-test 
${ALL_SOURCE_FILE}
)

target_include_directories(unit-test PRIVATE ${BaseeeLog} ${BaseeeString})

target_link_libraries(unit-test baseee-log baseee-string)

#安装
install(FILES 
${BaseeeLog}/log.hpp
${BaseeeString}/string.hpp
DESTINATION include
)

install(TARGETS
baseee-string
baseee-log 
DESTINATION lib
)