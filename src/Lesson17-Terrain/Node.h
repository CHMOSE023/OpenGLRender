#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "AABB.h"
#include "Renderable.h"

class Node
{
public:
    enum    FLAG
    {
        FLAG_UPDATE  = 1 << 0, // 0001
        FLAG_VISIBLE = 1 << 1, // 0010
        //0001 |= 0001  ->>  0001  1 FLAG_UPDATE 
        //0010 |= 0001  ->>  0011  3
        //0001 |= 0010  ->>  0011  3
        //0010 |= 0010  ->>  0010  2 FLAG_VISIBLE                        
        //0011 |= 0001  ->>  0011  3 
        //0011 |= 0010  ->>  0010  3  
    };
public:
    Node();
     ~Node();

    // 设置父节点
    void SetParent(Node* parent);

    // 获取父节点
    Node* GetParent() const;

    // 添加子节点
    void AddChild(Node* child);

    // 移除子节点
    void RemoveChild(Node* child);

    // 设置缩放
    void SetScale(const glm::vec3& scale);

    // 获取缩放
    glm::vec3 GetScale() const;

    // 设置位置
    void SetPosition(const glm::vec3& position);

    // 获取位置
    glm::vec3 GetPosition() const;

    // 设置旋转（四元数）
    void SetRotation(const glm::quat& rotation);

    // 获取旋转（四元数）
    glm::quat GetRotation() const;

    // 是否可见
    bool GetVisible()const;

    // 设置标志为
    void SetVisible(unsigned flag, bool );
   
    // 设置包围盒
    void SetAABB(const AABB& aabb);

    // 获取包围盒
    AABB GetAABB() const;

    // 获取节点模型矩阵
    glm::mat4 GetModelMatrix() const;

    // 渲染函数（虚函数，由子类实现具体的渲染操作）
    virtual void Render(ThirdCamera& camera, const glm::mat4& model) const;

    // 设置渲染对象
    void SetRenderable(Renderable* renderable);

    // 设置更新标志为
    void SetUpdate(bool flag = true);

    // 需要更新
    bool NeedUpdate()const;

    // 更新矩阵
    void Update(bool force = false);
    // 更新包围盒变换
    //void UpdateAABBTransform();

public:
    Node*              m_parent;           // 父节点指针
    std::vector<Node*> m_children;         // 子节点容器

    glm::vec3          m_scale;            // 缩放
    glm::vec3          m_position;         // 位置
    glm::quat          m_rotation;         // 旋转（四元数）   
    unsigned           m_flag;             // 标志位
    AABB               m_aabb;             // AABB包围盒
                       
    glm::mat4          m_modelMatrix;      // 模型矩阵
    Renderable*        m_renderable;       // 可渲染的

   
};
