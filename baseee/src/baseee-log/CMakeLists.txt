#构建
add_library(baseee-log "log.hpp" "log.cpp" )

#安装
install (TARGETS baseee-log DESTINATION bin)
install (FILES "log.hpp" DESTINATION include)