#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

GLuint programID;
GLFWwindow* window;

const GLuint WIDTH = 800, HEIGHT = 600;

GLfloat vertices[] = {
    // ¶¥µã×ø±ê           // ÑÕÉ«
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // ×óÏÂ½Ç (ºì)
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // ÓÒÏÂ½Ç (ÂÌ)
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // ÓÒÉÏ½Ç (À¶)
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // ×óÉÏ½Ç (»Æ)
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, // ×óÏÂ½Ç (Æ·ºì)
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // ÓÒÏÂ½Ç (Çà)
     0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, // ÓÒÉÏ½Ç (»Ò)
    -0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f  // ×óÉÏ½Ç (»Ò)
};

GLuint indices[] = {
    0, 1, 2,
    0, 2, 3,
    1, 5, 6,
    1, 6, 2,
    5, 4, 7,
    5, 7, 6,
    4, 0, 3,
    4, 3, 7,
    3, 2, 6,
    3, 6, 7,
    4, 5, 1,
    4, 1, 0
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexShaderSource = "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) in vec3 color;\n"
        "out vec3 vertexColor;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "   gl_Position = projection * view * model * vec4(position, 1.0);\n"
        "   vertexColor = color;\n"
        "}\0";
    glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderID);

    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentShaderSource = "#version 330 core\n"
        "in vec3 vertexColor;\n"
        "out vec4 color;\n"
        "void main() {\n"
        "   color = vec4(vertexColor, 1.0);\n"
        "}\n";
    glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderID);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Cube", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    initOpenGL();



    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 model(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        GLfloat currentTime = glfwGetTime();
        model=glm::mat4(1);
        model = glm::rotate(model, glm::radians(50.0f) * currentTime, glm::vec3(0.5f, 1.0f, 0.0f));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);

        GLuint modelLoc = glGetUniformLocation(programID, "model");
        GLuint viewLoc = glGetUniformLocation(programID, "view");
        GLuint projectionLoc = glGetUniformLocation(programID, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}
