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
        FLAG_UPDATE  = 1 << 0,
        FLAG_VISIBLE = 1 << 1,
    };
public:
    Node() 
        : m_parent(nullptr)
        , m_scale(glm::vec3(1.0f))
        , m_position(glm::vec3(0.0f))
        , m_rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
        , m_enabled(true), m_aabb()
        , m_modelMatrix(1.0f) {}
    virtual ~Node() {}

    // 设置父节点
    void SetParent(Node* parent) { m_parent = parent; }
    // 获取父节点
    Node* GetParent() const { return m_parent; }

    // 添加子节点
    void AddChild(Node* child) {
        child->SetParent(this);
        m_children.push_back(child);
    }

    // 移除子节点
    void RemoveChild(Node* child) {
        auto it = std::find(m_children.begin(), m_children.end(), child);
        if (it != m_children.end()) {
            (*it)->SetParent(nullptr);
            m_children.erase(it);
        }
    }

    // 设置缩放
    void SetScale(const glm::vec3& scale) 
    { 
        m_scale = scale; 
        UpdateTransform(); 
    }
    // 获取缩放
    glm::vec3 GetScale() const { return m_scale; }

    // 设置位置
    void SetPosition(const glm::vec3& position) { m_position = position; UpdateTransform(); }
    // 获取位置
    glm::vec3 GetPosition() const { return m_position; }

    // 设置旋转（四元数）
    void SetRotation(const glm::quat& rotation) 
    {
        m_rotation = rotation; 
        UpdateTransform();
        m_flag |= FLAG_UPDATE;
    }
    // 获取旋转（四元数）
    glm::quat GetRotation() const { return m_rotation; }

    // 设置是否启用
    void SetEnabled(bool enabled) { m_enabled = enabled; }
    // 获取是否启用
    bool IsEnabled() const { return m_enabled; }

    // 设置包围盒
    void SetAABB(const AABB& aabb) { m_aabb = aabb; }
    // 获取包围盒
    AABB GetAABB() const { return m_aabb; }

    // 获取节点模型矩阵
    glm::mat4 GetModelMatrix() const { return m_modelMatrix; }

    // 渲染函数（虚函数，由子类实现具体的渲染操作）
    virtual void Render(ThirdCamera& camera, const glm::mat4& model) const
    {
        if (m_renderable)
        {
            m_renderable->Render(camera, model);
        }
    }

    // 更新函数（虚函数，由子类实现具体的更新操作）
    virtual void SetRenderable(Renderable* renderable)
    {
        m_renderable = renderable;
        m_aabb       = renderable->GetBound();

        m_aabb.Transform(m_modelMatrix);

        m_flag |= FLAG_UPDATE; // 按位或
       
    }

protected:
    // 更新变换
    void UpdateTransform()
    {
        m_modelMatrix = glm::mat4(1.0f);
        m_modelMatrix = glm::translate(m_modelMatrix, m_position);
        m_modelMatrix *= glm::mat4_cast(m_rotation);
        m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

        // 更新包围盒矩阵
        UpdateAABBTransform();
    }

    // 更新包围盒变换
    void UpdateAABBTransform()
    {
        // 获取原始包围盒的最小和最大顶点
        glm::vec3 minCorner = m_aabb.GetMinCorner();
        glm::vec3 maxCorner = m_aabb.GetMaxCorner();

        // 对原始包围盒的最小和最大顶点进行变换
        glm::vec4 newMinCorner = m_modelMatrix * glm::vec4(minCorner, 1.0f);
        glm::vec4 newMaxCorner = m_modelMatrix * glm::vec4(maxCorner, 1.0f);

        // 更新包围盒的位置和大小
        m_aabb = AABB(glm::vec3(newMinCorner), glm::vec3(newMaxCorner));
    }

protected:
    Node*              m_parent;           // 父节点指针
    std::vector<Node*> m_children;         // 子节点容器

    glm::vec3          m_scale;            // 缩放
    glm::vec3          m_position;         // 位置
    glm::quat          m_rotation;         // 旋转（四元数）
    bool               m_enabled;          // 是否启用
    unsigned           m_flag;             // 标志位
    AABB               m_aabb;             // AABB包围盒
                       
    glm::mat4          m_modelMatrix;      // 模型矩阵
    Renderable*        m_renderable;       // 可渲染的

   
};
