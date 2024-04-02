cmake_minimum_required (VERSION 3.8)
project ("OpenGLRender")


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/include/") # 包含文件搜索目录
link_directories   ("${CMAKE_CURRENT_SOURCE_DIR}/deps/lib")      # 连接器搜索目录

set( SRCES
	"Lesson01-glfw" # 01-使用 glfw 建立OpenGL窗口
)

foreach(Src ${SRCES} )		

    message(${Src})
    file(GLOB SrcFile  "src/${Src}/*.h"  "src/${Src}/*.cpp" )
    add_executable (${Src}  ${SrcFile} )
    target_link_libraries(${Src} glfw3 openGL32  )
endforeach()

