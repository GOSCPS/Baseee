#构建
add_library(baseee-string string.cpp string.hpp )

#安装
install (TARGETS baseee-string DESTINATION bin)
install (FILES string.hpp DESTINATION include)