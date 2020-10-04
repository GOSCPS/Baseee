# Baseee
![Line](https://img.shields.io/tokei/lines/github/chhdao/Baseee)
![GitHub](https://img.shields.io/github/license/chhdao/Baseee)
![GitHub repo size](https://img.shields.io/github/repo-size/chhdao/Baseee)
![c++ Version](https://img.shields.io/badge/C%2B%2B-17-blue)
<hr>   

[English](https://github.com/chhdao/Baseee/blob/master/docs/README.md)
 
<hr>   

Baseee是一个跨平台c++程序库   
旨在扩展c++   
本项目分为以下模块：   
 + log 日志   
 + string  字符串处理   
 + parser 各种解析器   
 + components 各种工具
欢迎捐款or贡献代码  

## Build
Baseee可以在很多平台构建，使用Cmake构建系统   
```
$ git clone https://github.com/chhdao/Baseee --depth=1
$ cd Baseee/baseee
$ mkdir Build
$ cd Build
$ cmake ..
$ cmake --build .
$ cmake --install .
```
即可完成源码安装。    

你也可以使用Vcpkg:  
```
$ vcpkg install baseee
```
最后，将下面的内容加入你的CMakeLists.txt
```
find_package(Baseee CONFIG REQUIRED)
target_link_libraries(main PRIVATE baseee::baseee)
```
[文档](https://github.com/chhdao/Baseee/blob/master/docs/zh-cn/index.md)   
Enjoy!  
