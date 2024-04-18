#pragma once 
#include  "../Shader/Shader.h"
#include  <map>
#include <string>
// ����
class ShaderMaterials : public Shader
{
public:
    ShaderMaterials() {};
    ~ShaderMaterials() {};

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
  
            struct  Material {
                 vec3 ambient;     // ��������
                 vec3 diffuse;     // ���������
                 vec3 specular;    // �������
                 float shininess;  // �����
            };

            struct Light {
                vec3 position;     // λ��           
                vec3 ambient;      // ������
                vec3 diffuse;      // �������
                vec3 specular;     // �����
            };
          
            in vec3 Normal;  
            in vec3 FragPos;  
              
           
            uniform vec3     viewPos;   // �۲췽��
            uniform Material material;  // ʹ�ýṹ��
            uniform Light    light;     // ʹ�ýṹ��
            
            void main()
            {
                // ambient ������             
                vec3 ambient = light.ambient * material.ambient;
              	
                // diffuse  ������
                vec3 norm      = normalize(Normal);
                vec3 lightDir  = normalize(light.position - FragPos);
                float diff     = max(dot(norm, lightDir), 0.0);
                vec3 diffuse   = light.diffuse *  (diff * material.diffuse);
                
                // specular �����                
                vec3 viewDir    = normalize(viewPos - FragPos);
                vec3 reflectDir = reflect(-lightDir, norm);  
                float spec      = pow(max(dot(viewDir, reflectDir), 0.0),  material.shininess); 
                vec3 specular   = light.specular * (spec * material.specular);  
                    
                vec3 result = ambient + diffuse + specular;
                FragColor = vec4(result, 1.0);
            } 
          )";
       
     
        // 0(34) : error C1009 : "lightPos" is not member of struct "Light"
        // 0(42) : error C1503 : undefined variable "specularStrength"
        // 0(42) : error C1503 : undefined variable "lightColor"

        bool    res = CreateShader(vs, ps);

        if (res)
        {
            m_position   = glGetAttribLocation(m_shaderId, "aPos");
            m_normal     = glGetAttribLocation(m_shaderId, "aNormal");

            uniform["model"]              = glGetUniformLocation(m_shaderId, "model");
            uniform["view"]               = glGetUniformLocation(m_shaderId, "view");
            uniform["projection"]         = glGetUniformLocation(m_shaderId, "projection");

            uniform["viewPos"]            = glGetUniformLocation(m_shaderId, "viewPos");
            
            uniform["light.position"]     = glGetUniformLocation(m_shaderId, "light.position");
            uniform["light.ambient"]      = glGetUniformLocation(m_shaderId, "light.ambient");
            uniform["light.diffuse"]      = glGetUniformLocation(m_shaderId, "light.diffuse");
            uniform["light.specular"]     = glGetUniformLocation(m_shaderId, "light.specular");
            
            uniform["material.ambient"]   = glGetUniformLocation(m_shaderId, "material.ambient");
            uniform["material.diffuse"]   = glGetUniformLocation(m_shaderId, "material.diffuse");
            uniform["material.specular"]  = glGetUniformLocation(m_shaderId, "material.specular");
            uniform["material.shininess"] = glGetUniformLocation(m_shaderId, "material.shininess");
        }
        return true;
    }

public:
    unsigned m_position = -1;
    unsigned m_normal   = -1;

};

