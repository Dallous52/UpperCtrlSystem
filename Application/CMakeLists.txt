file(GLOB APP_SOURCES *.cpp)

add_subdirectory(SysApp)
add_subdirectory(Extender)

add_library(Application STATIC ${APP_SOURCES})

target_link_libraries(Application SysApp Extender)