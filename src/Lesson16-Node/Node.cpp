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

// ���ø��ڵ�
void Node::SetParent(Node* parent)
{
    m_parent = parent;
}

// ��ȡ���ڵ�
Node* Node::GetParent() const
{
    return m_parent;
}

// ����ӽڵ�
void Node::AddChild(Node* child)
{
    child->SetParent(this);
    m_children.push_back(child);
}

// �Ƴ��ӽڵ�
void Node::RemoveChild(Node* child)
{
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end()) {
        (*it)->SetParent(nullptr);
        m_children.erase(it);
    }
}

// ��������
void Node::SetScale(const glm::vec3& scale)
{
    m_scale = scale;
    m_flag |= FLAG_UPDATE;  // ���±�־λ
}

// ��ȡ����
glm::vec3 Node::GetScale() const
{
    return m_scale;
}

// ����λ��
void Node::SetPosition(const glm::vec3& position)
{
    m_position  = position;
    m_flag     |= FLAG_UPDATE;  // ���±�־λ   
}

// ��ȡλ��
glm::vec3 Node::GetPosition() const
{
    return m_position;
}

// ������ת����Ԫ����
void Node::SetRotation(const glm::quat& rotation)
{
    m_rotation = rotation;
    m_flag    |= FLAG_UPDATE; // ���±�־λ
}

// ��ȡ��ת����Ԫ����
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

// ���ð�Χ��
void Node::SetAABB(const AABB& aabb)
{
    m_aabb = aabb;
}

// ��ȡ��Χ��
AABB Node::GetAABB() const
{
    return m_aabb;
}

// ��ȡ�ڵ�ģ�;���
glm::mat4 Node::GetModelMatrix() const
{
    return m_modelMatrix;
}

// ��Ⱦ�������麯����������ʵ�־������Ⱦ������
void Node::Render(ThirdCamera& camera, const glm::mat4& model) const
{
    if (m_renderable)
    {
        m_renderable->Render(camera, model);
    }
}

// ������Ⱦ����
void Node::SetRenderable(Renderable* renderable)
{
    m_renderable = renderable;
    m_aabb       = renderable->GetBound();

    m_aabb.Transform(m_modelMatrix);

    m_flag |= FLAG_UPDATE; // ��λ��       
}

//  ���ø��±�־Ϊ
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
        m_modelMatrix = glm::translate(m_modelMatrix, m_position); // ����λ��
        m_modelMatrix = glm::scale(m_modelMatrix, m_scale);        // ��������
        m_modelMatrix = m_modelMatrix * glm::toMat4(m_rotation);   // ������ת
        m_aabb        = m_renderable->GetBound();
        m_aabb.Transform(m_modelMatrix);
    }
    else if (m_flag & FLAG_UPDATE)
    {
        m_modelMatrix = glm::translate(m_modelMatrix, m_position); // ����λ��
        m_modelMatrix = glm::scale(m_modelMatrix, m_scale);        // ��������
        m_modelMatrix = m_modelMatrix * glm::toMat4(m_rotation);   // ������ת
        m_aabb = m_renderable->GetBound();
        m_aabb.Transform(m_modelMatrix);
    }
}
