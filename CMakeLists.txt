cmake_minimum_required (VERSION 3.8)
project ("OpenGLRender")


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/include/") # 包含文件搜索目录
link_directories   ("${CMAKE_CURRENT_SOURCE_DIR}/deps/lib")      # 连接器搜索目录

set( SRCES
	"Lesson01-glfw"      # 01-使用 glfw 建立OpenGL窗口
	"Lesson02-App"       # 02-封装窗口
    "Lesson03-texture2D" # 03-使用2D纹理
)

set(GLAD "${CMAKE_CURRENT_SOURCE_DIR}/deps/include/glad/glad.c")

# 复制textures编译目录
file(GLOB Textures "${CMAKE_CURRENT_SOURCE_DIR}/deps/resources/textures/*.*") 
file(COPY ${Textures} DESTINATION textures/)


foreach(Src ${SRCES} )	

    message(${Src})
    file(GLOB SrcFile  "src/${Src}/*.h"  "src/${Src}/*.cpp" ${GLAD})
    add_executable (${Src}  ${SrcFile} )
    target_link_libraries(${Src} glfw3 openGL32  )
endforeach()

