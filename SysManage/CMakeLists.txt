aux_source_directory(. DIR_SRCS)

add_library(SysManage ${DIR_SRCS})

target_link_libraries(SysManage Application)