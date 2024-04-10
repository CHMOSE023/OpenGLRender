# CMake配置文件
cmake_minimum_required (VERSION 3.8)
project ("OpenGLRender")

# 搜索目录
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/include/") # 包含文件搜索目录
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/include/glew-2.1.0/") # 包含文件搜索目录
link_directories   ("${CMAKE_CURRENT_SOURCE_DIR}/deps/lib")      # 连接器搜索目录

# src内的文件夹
set( SRC_DIRES
	"Test01-Ray"            # 射线
	"Test02-Buffer"         # 缓冲区
	"Test03-Nuklear"        # NuklearUI
	"Test04-VAO"            # 测试 VAO VBO EBO
	"Lesson01-GLFW"         # 01-使用 glfw 建立OpenGL窗口
	"Lesson02-App"          # 02-封装窗口
    "Lesson03-Texture2D"    # 03-使用2D纹理
    "Lesson04-MVP"          # 04-矩阵：模型M、观察V、投影P 
    "Lesson05-Camera"       # 05-摄像机 第一人称 
    "Lesson06-Camera3rd"    # 06-摄像机 第三人称 
    "Lesson07-VertexBuffer" # 07-顶点缓冲区 
    "Lesson08-FrameBuffer"  # 08-帧缓冲 
    "Lesson09-Alphablend"   # 09-混合
    "Lesson10-Model"        # 10-外部模型
    "Lesson11-Animation2D"  # 12-动画2D
    
)

# glad文件
set(GLAD_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/include/glad/glad.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/include/glad/glad.c"
)


# 复制textures编译目录
file(GLOB Textures "${CMAKE_CURRENT_SOURCE_DIR}/deps/resources/*" 
                   "${CMAKE_CURRENT_SOURCE_DIR}/deps/dll/*") 
file(COPY ${Textures} DESTINATION  ${CMAKE_CURRENT_BINARY_DIR} )


# 添加glad库
add_library(glad ${GLAD_SRC})

# 遍历src文件夹内文件，添加exe程序
foreach(Src ${SRC_DIRES} )	
    message(${Src})
    file(GLOB SrcFile  "src/${Src}/*.h"  "src/${Src}/*.hpp"  "src/${Src}/*.cpp" "src/${Src}/*.c" )
    add_executable (${Src}  ${SrcFile} )
    target_link_libraries(${Src} glfw3 openGL32 glad )
endforeach()

target_link_libraries(Test03-Nuklear  glew32 )
