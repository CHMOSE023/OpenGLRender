# CMake配置文件
cmake_minimum_required (VERSION 3.8)
project ("OpenGLRender")

# 搜索目录
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/include/")            # 包含文件搜索目录
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/include/glew-2.1.0/") # 包含文件搜索目录
link_directories   ("${CMAKE_CURRENT_SOURCE_DIR}/deps/lib")                 # 连接器搜索目录
link_directories   ("${CMAKE_CURRENT_SOURCE_DIR}/src/core")                 # 核心库

# 添加编译宏
add_compile_definitions(
  _CRT_SECURE_NO_WARNINGS  #fopen sscanf 警告
)

# src内的文件夹
set( SRC_DIRES
	"Test01-Ray"            # 射线
	"Test02-Buffer"         # 缓冲区
	"Test03-Nuklear"        # NuklearUI
	"Test04-VAO"            # 测试 VAO VBO EBO
	"Test05-Camera"         # 测试 Camera 旋转平移 
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
    "Lesson11-Animation2D"  # 11-动画基于图片
    "Lesson12-Animation3D"  # 12-动画基于关键帧
    "Lesson13-SkinBase"     # 13-骨骼动画节点原理
    "Lesson14-SkinModel"    # 14-播放模型中骨骼动画
    "Lesson15-Culling"      # 15-渲染视锥体内模型
    "Lesson16-Node"         # 16-场景节点
    "Lesson17-Terrain"      # 17-灰度图地形
    "Lesson18-Billboard"    # 18-布告板技术
    
)

# glad文件
set(GLAD_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/include/glad/glad.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/include/glad/glad.c"
)

# core文件
file(GLOB CORE_SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.h"  
  "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp"  
)

# 复制textures编译目录
file(GLOB Textures "${CMAKE_CURRENT_SOURCE_DIR}/deps/resources/*" 
                   "${CMAKE_CURRENT_SOURCE_DIR}/deps/dll/*") 
file(COPY ${Textures} DESTINATION  ${CMAKE_CURRENT_BINARY_DIR} )

message(---------->"${CORE_SRC}")

# 添加glad库
add_library(glad ${GLAD_SRC})
add_library(core ${CORE_SRC})

# 遍历src文件夹内文件，添加exe程序
foreach(Src ${SRC_DIRES} )	
    message(${Src})
    file(GLOB SrcFile  "src/${Src}/*.h"  "src/${Src}/*.hpp"  "src/${Src}/*.cpp" "src/${Src}/*.c" )
    add_executable (${Src}  ${SrcFile} )
    target_link_libraries(${Src} glfw3 openGL32 glad core)
endforeach()

target_link_libraries(Test03-Nuklear  glew32 )
