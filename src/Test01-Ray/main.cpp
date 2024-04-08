#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// 视图矩阵和投影矩阵
glm::mat4 projectionMatrix;
glm::mat4 viewMatrix;

// 用于存储鼠标点击的位置
double mouseX = 0, mouseY = 0;

// 屏幕坐标转换为世界坐标
glm::vec3 screenToWorld(double mouseX, double mouseY) 
{
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

    // 将屏幕坐标转换为标准化设备坐标 (NDC)
    float x = (2.0f * mouseX) / width - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / height;

    // 创建裁剪坐标
    glm::vec4 clipCoords = glm::vec4(x, y, -1.0f, 1.0f);

    // 创建逆投影矩阵和逆视图矩阵
    glm::mat4 inverseProjectionMatrix = glm::inverse(projectionMatrix);
    glm::mat4 inverseViewMatrix = glm::inverse(viewMatrix);

    // 将裁剪坐标转换为视图坐标
    glm::vec4 eyeCoords = inverseProjectionMatrix * clipCoords;
    eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f); // 方向向量

    // 将视图坐标转换为世界坐标
    glm::vec4 rayWorld = inverseViewMatrix * eyeCoords;
    glm::vec3 rayDirection = glm::normalize(glm::vec3(rayWorld));

    return rayDirection;
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods) 
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        glm::vec3 rayDirection = screenToWorld(xpos, ypos);

        // 输出射线方向向量的世界坐标
        std::cout << "Ray direction in world coordinates: (" << rayDirection.x << ", " << rayDirection.y << ", " << rayDirection.z << ")" << std::endl;

        // 计算拾取点的位置
        glm::vec3 cameraPosition = glm::vec3(glm::inverse(viewMatrix)[3]);
        glm::vec3 rayOrigin = cameraPosition;
        float distanceAlongRay = -rayOrigin.z / rayDirection.z;
        glm::vec3 pickPoint = rayOrigin + distanceAlongRay * rayDirection;

        // 输出拾取点的世界坐标
        std::cout << "Picked point in world coordinates: (" << pickPoint.x << ", " << pickPoint.y << ", " << pickPoint.z << ")" << std::endl;
    }
}

int main() {
    // 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 设置鼠标回调函数
    glfwSetMouseButtonCallback(window, mouse_callback);

    // 设置投影矩阵
    projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // 设置视图矩阵
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // 主循环
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    // 清理 GLFW
    glfwTerminate();
    return 0;
}
