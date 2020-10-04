# Baseee
![Line](https://img.shields.io/tokei/lines/github/chhdao/Baseee)
![GitHub](https://img.shields.io/github/license/chhdao/Baseee)
![GitHub repo size](https://img.shields.io/github/repo-size/chhdao/Baseee)
![c++ Version](https://img.shields.io/badge/C%2B%2B-17-blue)
<hr>    

Baseee is a c++ Cross-platform lib.
The lib has module:
 + log  
 + string   
 + parser   
 + components   

## Build
Baseee can build on Windows/Linux/Mac.Use Cmake to build.  
```
$ git clone https://github.com/chhdao/Baseee --depth=1
$ cd Baseee/baseee
$ mkdir Build
$ cd Build
$ cmake ..
$ cmake --build .
$ cmake --install .
```
Source code to complete the installation.       

Or you can use the vcpkg.(No supports now)
```
$ vcpkg install baseee
```
Finally, add the following content to CMakeLists.txt.
```
find_package(Baseee CONFIG REQUIRED)
target_link_libraries(main PRIVATE baseee::baseee)
```  
[Document](https://github.com/chhdao/Baseee/blob/master/docs/en-us/index.md)    
Enjoy!  
