# 安装Baseee
依赖：标准开发环境   
Baseee使用了C++17   

从源码安装
```
$ git clone https://github.com/chhdao/Baseee --depth=1
$ cd Baseee/baseee
$ mkdir Build
$ cd Build
$ cmake ..
$ cmake --build .
$ cmake --install .
```
你也可以使用vcpkg:
```
$ vcpkg install baseee
注意：baseee不支持x86和arm（但支持arm64）等32位平台
```
之后在CMakeLists.txt添加：  
```
find_package(Baseee CONFIG REQUIRED)
target_link_libraries(main PRIVATE baseee::baseee)
```
还需要显示声明使用c++17：
```
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```
最后：恭喜你安装成功