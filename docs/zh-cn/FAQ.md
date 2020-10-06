# FAQ常见问题
### 1.默认库MSVCRT与其他库冲突(error LNK2038)
添加:
```
if(WIN32)
add_compile_options("/MD")
endif()
```
到CMakeLists.txt即可  
另一个更好的解决方案是:切换到发布(release)构建(整个baseee在vcpkg中是以release的形式构建的) 
