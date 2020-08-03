#构建
add_library(baseee-log log.cpp log.hpp)

#安装
install (TARGETS baseee-log DESTINATION bin)
install (FILES log.hpp DESTINATION include)