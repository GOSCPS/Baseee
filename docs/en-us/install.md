# Install The Baseee Lib
No third party reliance
Baseee使用了C++17   

Install From Source Code
```
$ git clone https://github.com/chhdao/Baseee --depth=1
$ cd Baseee/baseee
$ mkdir Build
$ cd Build
$ cmake ..
$ cmake --build .
$ cmake --install .
```
Or use the vcpkg:
```
$ vcpkg install baseee
! baseee no supports x86 and arm(but does upports arm64)
```
Then add to CMakeLists.txt：  
```
find_package(Baseee CONFIG REQUIRED)
target_link_libraries(main PRIVATE baseee::baseee)
```
And Need to rely on c++17 
```
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```
Install OK! Enjoi!