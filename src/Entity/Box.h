#pragma once
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "Entity.h"
#include "../Core/Camera.h"
class Box :public Entity
{
private:    
	GLuint m_programID;
	GLuint m_vao, m_vbo, m_ebo;
public:
    Box()
    {
        m_programID = -1;
        m_vao = -1;
        m_vbo = -1;
        m_ebo = -1;
    };
	~Box()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
        glDeleteProgram(m_programID);

    };
	void Init()
	{

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

        m_programID = glCreateProgram();
        glAttachShader(m_programID, vertexShaderID);
        glAttachShader(m_programID, fragmentShaderID);
        glLinkProgram(m_programID);

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);



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


        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

	}

    void Render(const Camera &camera )
    {
        glm::mat4 model(1.0f);
        glm::mat4 view = camera.GetView();
        glm::mat4 projection = camera.GetProject();
        //
        GLfloat currentTime = glfwGetTime();
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.0, 0, 0));
        model = glm::rotate(model, glm::radians(50.0f) * currentTime, glm::vec3(0.5f, 1.0f, 0.0f));

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(m_programID);

        GLuint modelLoc = glGetUniformLocation(m_programID, "model");
        GLuint viewLoc = glGetUniformLocation(m_programID, "view");
        GLuint projectionLoc = glGetUniformLocation(m_programID, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(0);

    }

};
