OpenGL 渲染引擎基础

OpenGL是数字孪生、游戏引擎、CAD用到图形API，OpenGL功能强大，WebGL、OpenGL|ES 是其简化版，掌握了OpenGL也就掌握了WebGL、OpenGL|ES。
OpenGL运行在桌面电脑中；OpenGLES运行在手机中；WebGL运行在浏览器中。

Web应用：Babylon.js Three.js都是在WebGL基础上做的封装。这两个常用在数字孪生领域。

PC游戏引擎：UE5、Unity、Godot用到了Vulkan、Direct3D、OpenGL、OpenGLES、WebGL等图形API其中之一或全部。从图形引擎必须先从掌握其中一个API开始。

OpenGL渲染基础，以使用一个场景渲染为目标。介绍如何使用OpenGL。

从使用第三方软件建立窗口开始，介绍纹理、相机、模型、动画、场景、地形等应用案例。

通过这些案例掌握OpenGL基础缓存区基础：VAO VBO EBO 、帧缓冲等内容。

采用vs+CMakelist.txt，目前为止用到的第三方库：

glm(数学库)、

glew(窗口库)、

glad(扩展库)、

stb_image(图形读取)、

rapidxml（xml）

源码：https://github.com/CHMOSE023/OpenGLRenderer   

使用VS++ CMakeLists 参考文章

1.使用VS2022/2019/2017 + CMakeLists 编译c++代码

https://blog.csdn.net/qq_25547755/article/details/132194569

2.VS2022+ CMakeLists 编译 OpenGL编程指南第9版 (红宝书)

https://blog.csdn.net/qq_25547755/article/details/134643272

3.VS2022+ CMakeLists 编译 OpenGL超级宝典 第7版 (蓝宝书) 

https://blog.csdn.net/qq_25547755/article/details/134644642

后续会将这书中部分案例添加到本项目。