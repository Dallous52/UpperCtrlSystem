#获取所有文件
file(GLOB my_folders */)

set(DIRSRCS "") # 设置变量为空
foreach(folder ${my_folders})
  if(IS_DIRECTORY ${folder})
    GET_FILENAME_COMPONENT(folder_name ${folder} NAME)
       #把指定目录中的所有源文件的文件名存储在一个变量中
        aux_source_directory(${folder} DIRSRCS)
  endif()
endforeach()

add_library(Global STATIC ${DIRSRCS})