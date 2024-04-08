#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// ��ͼ�����ͶӰ����
glm::mat4 projectionMatrix;
glm::mat4 viewMatrix;

// ���ڴ洢�������λ��
double mouseX = 0, mouseY = 0;

// ��Ļ����ת��Ϊ��������
glm::vec3 screenToWorld(double mouseX, double mouseY) 
{
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

    // ����Ļ����ת��Ϊ��׼���豸���� (NDC)
    float x = (2.0f * mouseX) / width - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / height;

    // �����ü�����
    glm::vec4 clipCoords = glm::vec4(x, y, -1.0f, 1.0f);

    // ������ͶӰ���������ͼ����
    glm::mat4 inverseProjectionMatrix = glm::inverse(projectionMatrix);
    glm::mat4 inverseViewMatrix = glm::inverse(viewMatrix);

    // ���ü�����ת��Ϊ��ͼ����
    glm::vec4 eyeCoords = inverseProjectionMatrix * clipCoords;
    eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f); // ��������

    // ����ͼ����ת��Ϊ��������
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

        // ������߷�����������������
        std::cout << "Ray direction in world coordinates: (" << rayDirection.x << ", " << rayDirection.y << ", " << rayDirection.z << ")" << std::endl;

        // ����ʰȡ���λ��
        glm::vec3 cameraPosition = glm::vec3(glm::inverse(viewMatrix)[3]);
        glm::vec3 rayOrigin = cameraPosition;
        float distanceAlongRay = -rayOrigin.z / rayDirection.z;
        glm::vec3 pickPoint = rayOrigin + distanceAlongRay * rayDirection;

        // ���ʰȡ�����������
        std::cout << "Picked point in world coordinates: (" << pickPoint.x << ", " << pickPoint.y << ", " << pickPoint.z << ")" << std::endl;
    }
}

int main() {
    // ��ʼ�� GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // ��������
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // �������ص�����
    glfwSetMouseButtonCallback(window, mouse_callback);

    // ����ͶӰ����
    projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // ������ͼ����
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // ��ѭ��
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    // ���� GLFW
    glfwTerminate();
    return 0;
}
