#pragma once 
#include  "../Shader/Shader.h"
#include  <map>
#include <string>
// ¹âÔ´ÐÎ×´
class ShaderLighting : public Shader
{
public:
    ShaderLighting() {};
    ~ShaderLighting() {};

    virtual bool  Initialize()
    {
        const char* vs = R"(
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

        const char* ps = R"(
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

        bool    res = CreateShader(vs, ps);

        if (res)
        {
            m_position   = glGetAttribLocation(m_shaderId, "aPos");
            m_normal     = glGetAttribLocation(m_shaderId, "aNormal");


            m_model      = glGetUniformLocation(m_shaderId, "model");
            m_view       = glGetUniformLocation(m_shaderId, "view");
            m_projection = glGetUniformLocation(m_shaderId, "projection");

            m_lightPos     = glGetUniformLocation(m_shaderId, "lightPos");
            m_viewPos      = glGetUniformLocation(m_shaderId, "viewPos");          
            m_lightColor   = glGetUniformLocation(m_shaderId, "lightColor");
            m_objectColor  = glGetUniformLocation(m_shaderId, "objectColor");

            uniform["model"]      = m_model;
            uniform["view"]       = m_view;
            uniform["projection"] = m_projection;

            uniform["lightPos"]    = m_lightPos;
            uniform["viewPos"]     = m_viewPos;
            uniform["lightColor"]  = m_lightColor;
            uniform["objectColor"] = m_objectColor;

        }
        return true;
    }

public:
    unsigned m_position = -1;
    unsigned m_normal   = -1;

private:
    unsigned m_model = -1;
    unsigned m_view = -1;
    unsigned m_projection = -1;

    unsigned m_lightPos = -1;
    unsigned m_viewPos = -1;   
    unsigned m_lightColor = -1;
    unsigned m_objectColor = -1;

};

