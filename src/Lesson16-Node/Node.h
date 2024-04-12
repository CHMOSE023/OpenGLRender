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

    // ���ø��ڵ�
    void SetParent(Node* parent) { m_parent = parent; }
    // ��ȡ���ڵ�
    Node* GetParent() const { return m_parent; }

    // ����ӽڵ�
    void AddChild(Node* child) {
        child->SetParent(this);
        m_children.push_back(child);
    }

    // �Ƴ��ӽڵ�
    void RemoveChild(Node* child) {
        auto it = std::find(m_children.begin(), m_children.end(), child);
        if (it != m_children.end()) {
            (*it)->SetParent(nullptr);
            m_children.erase(it);
        }
    }

    // ��������
    void SetScale(const glm::vec3& scale) 
    { 
        m_scale = scale; 
        UpdateTransform(); 
    }
    // ��ȡ����
    glm::vec3 GetScale() const { return m_scale; }

    // ����λ��
    void SetPosition(const glm::vec3& position) { m_position = position; UpdateTransform(); }
    // ��ȡλ��
    glm::vec3 GetPosition() const { return m_position; }

    // ������ת����Ԫ����
    void SetRotation(const glm::quat& rotation) 
    {
        m_rotation = rotation; 
        UpdateTransform();
        m_flag |= FLAG_UPDATE;
    }
    // ��ȡ��ת����Ԫ����
    glm::quat GetRotation() const { return m_rotation; }

    // �����Ƿ�����
    void SetEnabled(bool enabled) { m_enabled = enabled; }
    // ��ȡ�Ƿ�����
    bool IsEnabled() const { return m_enabled; }

    // ���ð�Χ��
    void SetAABB(const AABB& aabb) { m_aabb = aabb; }
    // ��ȡ��Χ��
    AABB GetAABB() const { return m_aabb; }

    // ��ȡ�ڵ�ģ�;���
    glm::mat4 GetModelMatrix() const { return m_modelMatrix; }

    // ��Ⱦ�������麯����������ʵ�־������Ⱦ������
    virtual void Render(ThirdCamera& camera, const glm::mat4& model) const
    {
        if (m_renderable)
        {
            m_renderable->Render(camera, model);
        }
    }

    // ���º������麯����������ʵ�־���ĸ��²�����
    virtual void SetRenderable(Renderable* renderable)
    {
        m_renderable = renderable;
        m_aabb       = renderable->GetBound();

        m_aabb.Transform(m_modelMatrix);

        m_flag |= FLAG_UPDATE; // ��λ��
       
    }

protected:
    // ���±任
    void UpdateTransform()
    {
        m_modelMatrix = glm::mat4(1.0f);
        m_modelMatrix = glm::translate(m_modelMatrix, m_position);
        m_modelMatrix *= glm::mat4_cast(m_rotation);
        m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

        // ���°�Χ�о���
        UpdateAABBTransform();
    }

    // ���°�Χ�б任
    void UpdateAABBTransform()
    {
        // ��ȡԭʼ��Χ�е���С����󶥵�
        glm::vec3 minCorner = m_aabb.GetMinCorner();
        glm::vec3 maxCorner = m_aabb.GetMaxCorner();

        // ��ԭʼ��Χ�е���С����󶥵���б任
        glm::vec4 newMinCorner = m_modelMatrix * glm::vec4(minCorner, 1.0f);
        glm::vec4 newMaxCorner = m_modelMatrix * glm::vec4(maxCorner, 1.0f);

        // ���°�Χ�е�λ�úʹ�С
        m_aabb = AABB(glm::vec3(newMinCorner), glm::vec3(newMaxCorner));
    }

protected:
    Node*              m_parent;           // ���ڵ�ָ��
    std::vector<Node*> m_children;         // �ӽڵ�����

    glm::vec3          m_scale;            // ����
    glm::vec3          m_position;         // λ��
    glm::quat          m_rotation;         // ��ת����Ԫ����
    bool               m_enabled;          // �Ƿ�����
    unsigned           m_flag;             // ��־λ
    AABB               m_aabb;             // AABB��Χ��
                       
    glm::mat4          m_modelMatrix;      // ģ�;���
    Renderable*        m_renderable;       // ����Ⱦ��

   
};
