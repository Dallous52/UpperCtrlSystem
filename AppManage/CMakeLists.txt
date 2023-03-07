aux_source_directory(. DIR_SRCS)

find_package(Threads REQUIRED)

add_library(AppManage ${DIR_SRCS})

target_link_libraries(AppManage Global Threads::Threads)