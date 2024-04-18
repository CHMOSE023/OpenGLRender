#include "../Entity/Entity.h"
#include "../Core/Camera.h"
#include <glm/gtc/type_ptr.hpp>

class BoxColorLighting :public Entity
{

private:
    GLuint lightingShader;
    GLuint cubeShader;
    GLuint cubeVAO, lightVAO, VBO;


public:
    BoxColorLighting()
	{
      // m_vaoCube  = -1;
      // m_vaoLight = -1;
      // m_vbo      = -1;
	};
	~BoxColorLighting()
	{
        glDeleteVertexArrays(1, &cubeVAO);
        glDeleteVertexArrays(1, &lightVAO);
        glDeleteBuffers(1, &VBO);    
        glDeleteProgram(lightingShader);
        glDeleteProgram(cubeShader);
	
	};
   
	virtual void Init()
	{
        const GLchar* lightingVS = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aNormal;
            
            out vec3 FragPos;
            out vec3 Normal;
            
            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;
            
            void main()
            {
                FragPos = vec3(model * vec4(aPos, 1.0));
                Normal = mat3(transpose(inverse(model))) * aNormal;  
                
                gl_Position = projection * view * vec4(FragPos, 1.0);
            }
        )";
       
        const GLchar* lightingFS = R"(
            #version 330 core
            out vec4 FragColor;
            
            in vec3 Normal;  
            in vec3 FragPos;  
              
            uniform vec3 lightPos; 
            uniform vec3 viewPos; 
            uniform vec3 lightColor;
            uniform vec3 objectColor;
            
            void main()
            {
                // ambient
                float ambientStrength = 0.1;
                vec3 ambient = ambientStrength * lightColor;
              	
                // diffuse 
                vec3 norm = normalize(Normal);
                vec3 lightDir = normalize(lightPos - FragPos);
                float diff = max(dot(norm, lightDir), 0.0);
                vec3 diffuse = diff * lightColor;
                
                // specular
                float specularStrength = 0.5;
                vec3 viewDir = normalize(viewPos - FragPos);
                vec3 reflectDir = reflect(-lightDir, norm);  
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), 50); 
                vec3 specular = specularStrength * spec * lightColor;  
                    
                vec3 result = (ambient + diffuse + specular) * objectColor;
                FragColor = vec4(result, 1.0);
            } 
         )";
     

        const GLchar* cubeVS = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            
            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;
            
            void main()
            {
            	gl_Position = projection * view * model * vec4(aPos, 1.0);
            }
        )";

        const GLchar* cubeFS = R"(
            #version 330 core
            out vec4 FragColor;
            
            void main()
            {
                FragColor = vec4(1.0); // set all 4 vector values to 1.0
            }
         )";


        // 创建 shader
        lightingShader = CreateShader(lightingVS, lightingFS);
        cubeShader     = CreateShader(cubeVS, cubeFS);


        float vertices[] = {
          -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          
          -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
           0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
           0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
           0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
          -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
          -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
          
          -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
          -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
          -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
          -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
          -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
          -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
          
           0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
           0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
           0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
           0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
           0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
           0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
          
          -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
           0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
           0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
           0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
          
          -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
           0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
           0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
           0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
          -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
          -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

       
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // 盒子
        glBindVertexArray(cubeVAO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // position attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);


       
        // 光源
        glGenVertexArrays(1, &lightVAO);
        glBindVertexArray(lightVAO);

        // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);



	}

	virtual void  Render(const Camera &camera )
	{
       
        // lighting
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        glm::mat4 projectionMat = camera.GetProject();
        glm::mat4 viewMat = camera.GetView();
        glm::mat4 modelMat = glm::mat4(1.0f);

        {  // 绘制物体 

            glUseProgram(lightingShader);

            modelMat = glm::rotate(modelMat, (float)glfwGetTime(), glm::vec3(1, 1, 0));

            SetVec3(lightingShader,"objectColor", 1.0f, 0.5f, 0.31f);
            SetVec3(lightingShader,"lightColor",  1.0f, 1.0f, 1.0f);
            SetVec3(lightingShader,"lightPos",    lightPos);
            SetVec3(lightingShader,"viewPos",     camera.GetEye());  // 相机位置

            SetMat4(lightingShader,"projection",  projectionMat);
            SetMat4(lightingShader,"view",        viewMat);
            SetMat4(lightingShader,"model",       modelMat);
          
            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);

        }

        {  // 绘制光源          
           

            modelMat = glm::mat4(1.0f);
            modelMat = glm::translate(modelMat, lightPos);
            modelMat = glm::scale(modelMat, glm::vec3(0.2f)); // a smaller cube

            glUseProgram(cubeShader);

            SetMat4(cubeShader, "projection", projectionMat);
            SetMat4(cubeShader, "view",       viewMat);
            SetMat4(cubeShader, "model",      modelMat);

            glBindVertexArray(lightVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

	};

    void SetVec3(unsigned shader,const char* name, const float x, const float y, const float z)const
    {

        GLuint uniform3f = glGetUniformLocation(shader, name);
        glUniform3f(uniform3f, x, y, z);

    }

    void SetVec3(unsigned shader, const char* name, const glm::vec3 vec) const
    {
        GLuint uniform3f = glGetUniformLocation(shader, name);
        glUniform3f(uniform3f, vec.x, vec.y, vec.z);
    }

    void SetMat4(unsigned shader, const char* name, const glm::mat4 &mat) const
    {
        GLuint mat4fv = glGetUniformLocation(shader, name);
        glUniformMatrix4fv(mat4fv, 1, GL_FALSE, glm::value_ptr(mat));

    }

    unsigned CreateShader(const char* vertex, const char* fragment)
    {
        unsigned  shaderId;
        bool error          = false;
        int  vertexShader   = 0;
        int  fragmentShader = 0;

        do
        {
            if (vertex)
            {
                vertexShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShader, 1, &vertex, 0);
                glCompileShader(vertexShader);

                GLint   compileStatus;
                glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
                error = compileStatus == GL_FALSE;
                if (error)
                {
                    GLchar messages[256];
                    glGetShaderInfoLog(vertexShader, sizeof(messages), 0, messages);
                    printf("s", messages);
                    assert(messages && 0 != 0);
                    break;
                }
            }

            if (fragment)
            {
                fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShader, 1, &fragment, 0);
                glCompileShader(fragmentShader);

                GLint   compileStatus;
                glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
                error = compileStatus == GL_FALSE;

                if (error)
                {
                    GLchar messages[256];
                    glGetShaderInfoLog(fragmentShader, sizeof(messages), 0, messages);
                    printf("s", messages);
                    assert(messages && 0 != 0);
                    break;
                }
            }
            shaderId = glCreateProgram();

            if (vertexShader)
            {
                glAttachShader(shaderId, vertexShader);
            }

            if (fragmentShader)
            {
                glAttachShader(shaderId, fragmentShader);
            }

            glLinkProgram(shaderId);

            GLint linkStatus;
            glGetProgramiv(shaderId, GL_LINK_STATUS, &linkStatus);
            if (linkStatus == GL_FALSE)
            {
                GLchar messages[256];
                glGetProgramInfoLog(shaderId, sizeof(messages), 0, messages);
                break;
            }
            glUseProgram(shaderId);

        } while (false);

        if (error)
        {
            if (fragmentShader)
            {
                glDeleteShader(fragmentShader);
                fragmentShader = 0;
            }
            if (vertexShader)
            {
                glDeleteShader(vertexShader);
                vertexShader = 0;
            }
            if (shaderId)
            {
                glDeleteProgram(shaderId);
                shaderId = 0;
            }
        }

        return shaderId;

    }

};
