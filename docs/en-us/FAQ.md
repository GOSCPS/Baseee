# FAQ
### 1.The default library MSVCRT conflicts with other libraries(error LNK2038)
Add:
```
if(WIN32)
add_compile_options("/MD")
endif()
```
To CMakeLists.txt  
Another better solution is: switch to release (release) build (the entire baseee is used in the form of Realease).