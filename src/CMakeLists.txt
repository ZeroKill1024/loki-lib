
file(GLOB SRCS "*.cpp")

add_library(Loki SHARED ${SRCS})
add_library(Loki-static STATIC ${SRCS})


set_target_properties(Loki PROPERTIES OUTPUT_NAME "loki")
# 指定静态库的输出名称
set_target_properties(Loki-static PROPERTIES OUTPUT_NAME "loki")
# 使动态库和静态库同时存在
set_target_properties(Loki PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(Loki-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
 
# 指定动态库版本
# VERSION 动态库版本
# SOVERSION API版本
set_target_properties(Loki PROPERTIES VERSION 0.1.7 SOVERSION 0.1.7)
 
# 将动态库与动态库同时安装到lib目录中
install (TARGETS Loki Loki-static DESTINATION lib)