#构建
add_library(baseee-string  "string.hpp" "string.cpp" "coder.cpp")

#安装
install (TARGETS baseee-string DESTINATION bin)
install (FILES "string.hpp" DESTINATION include)