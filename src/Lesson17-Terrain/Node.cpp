#include "Node.h"
#include <glm/gtx/quaternion.hpp>

Node::Node()
    : m_parent(nullptr)
    , m_scale(glm::vec3(1.0f))
    , m_position(glm::vec3(0.0f))
    , m_rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))    
    , m_aabb()
    , m_modelMatrix(1.0f)
{
    m_flag = FLAG_UPDATE;
}

Node::~Node()
{
}

// 设置父节点
void Node::SetParent(Node* parent)
{
    m_parent = parent;
}

// 获取父节点
Node* Node::GetParent() const
{
    return m_parent;
}

// 添加子节点
void Node::AddChild(Node* child)
{
    child->SetParent(this);
    m_children.push_back(child);
}

// 移除子节点
void Node::RemoveChild(Node* child)
{
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end()) {
        (*it)->SetParent(nullptr);
        m_children.erase(it);
    }
}

// 设置缩放
void Node::SetScale(const glm::vec3& scale)
{
    m_scale = scale;
    m_flag |= FLAG_UPDATE;  // 更新标志位
}

// 获取缩放
glm::vec3 Node::GetScale() const
{
    return m_scale;
}

// 设置位置
void Node::SetPosition(const glm::vec3& position)
{
    m_position  = position;
    m_flag     |= FLAG_UPDATE;  // 更新标志位   
}

// 获取位置
glm::vec3 Node::GetPosition() const
{
    return m_position;
}

// 设置旋转（四元数）
void Node::SetRotation(const glm::quat& rotation)
{
    m_rotation = rotation;
    m_flag    |= FLAG_UPDATE; // 更新标志位
}

// 获取旋转（四元数）
glm::quat Node::GetRotation() const
{
    return m_rotation;
}

bool Node::GetVisible() const
{
    return  (m_flag & FLAG_VISIBLE) ? true : false;
}

void Node::SetVisible(unsigned flag, bool merge = true)
{
    if (merge)
    {
        m_flag |= flag;
    }
    else
    {
        m_flag = flag;
    }
}

// 设置包围盒
void Node::SetAABB(const AABB& aabb)
{
    m_aabb = aabb;
}

// 获取包围盒
AABB Node::GetAABB() const
{
    return m_aabb;
}

// 获取节点模型矩阵
glm::mat4 Node::GetModelMatrix() const
{
    return m_modelMatrix;
}

// 渲染函数（虚函数，由子类实现具体的渲染操作）
void Node::Render(ThirdCamera& camera, const glm::mat4& model) const
{
    if (m_renderable)
    {
        m_renderable->Render(camera, model);
    }
}

// 设置渲染对象
void Node::SetRenderable(Renderable* renderable)
{
    m_renderable = renderable;
    m_aabb       = renderable->GetBound();

    m_aabb.Transform(m_modelMatrix);

    m_flag |= FLAG_UPDATE; // 按位或       
}

//  设置更新标志为
void Node::SetUpdate(bool flag)
{
    if (flag)
    {
        m_flag |= FLAG_UPDATE;
    }
    else
    {
        m_flag &= ~FLAG_UPDATE;
    }
}

bool Node::NeedUpdate()const
{
    return  m_flag & FLAG_UPDATE;
}

void Node::Update(bool force)
{
    if (force)
    {
        m_modelMatrix = glm::translate(m_modelMatrix, m_position); // 加入位置
        m_modelMatrix = glm::scale(m_modelMatrix, m_scale);        // 加入缩放
        m_modelMatrix = m_modelMatrix * glm::toMat4(m_rotation);   // 加入旋转
        m_aabb        = m_renderable->GetBound();
        m_aabb.Transform(m_modelMatrix);
    }
    else if (m_flag & FLAG_UPDATE)
    {
        m_modelMatrix = glm::translate(m_modelMatrix, m_position); // 加入位置
        m_modelMatrix = glm::scale(m_modelMatrix, m_scale);        // 加入缩放
        m_modelMatrix = m_modelMatrix * glm::toMat4(m_rotation);   // 加入旋转
        m_aabb = m_renderable->GetBound();
        m_aabb.Transform(m_modelMatrix);
    }
}
