cmake_minimum_required(VERSION 3.1)
project(UpperCtrlSystem)

#设置c++11标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
message("INCLUDE_DIRS: ${INCLUDE_DIRS}")

file(GLOB my_folders "${INCLUDE_DIRS}/*")

foreach(folder ${my_folders})
  if(IS_DIRECTORY ${folder})
    GET_FILENAME_COMPONENT(folder_name ${folder} NAME)
    #打印信息
    message("folder_name: ${folder_name}, path: ${folder}")
    #把指定目录中的所有源文件的文件名存储在一个变量中
    include_directories(${folder})
  endif()
endforeach()

add_subdirectory(SysManage)
add_subdirectory(Global)
add_subdirectory(AppManage)
add_subdirectory(Application)

add_executable(UpperCtrlSystem Main.cpp)

target_link_libraries(UpperCtrlSystem SysManage)