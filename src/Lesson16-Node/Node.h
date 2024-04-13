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

    // ���ø��ڵ�
    void SetParent(Node* parent);

    // ��ȡ���ڵ�
    Node* GetParent() const;

    // ����ӽڵ�
    void AddChild(Node* child);

    // �Ƴ��ӽڵ�
    void RemoveChild(Node* child);

    // ��������
    void SetScale(const glm::vec3& scale);

    // ��ȡ����
    glm::vec3 GetScale() const;

    // ����λ��
    void SetPosition(const glm::vec3& position);

    // ��ȡλ��
    glm::vec3 GetPosition() const;

    // ������ת����Ԫ����
    void SetRotation(const glm::quat& rotation);

    // ��ȡ��ת����Ԫ����
    glm::quat GetRotation() const;

    // �Ƿ�ɼ�
    bool GetVisible()const;

    // ���ñ�־Ϊ
    void SetVisible(unsigned flag, bool );
   
    // ���ð�Χ��
    void SetAABB(const AABB& aabb);

    // ��ȡ��Χ��
    AABB GetAABB() const;

    // ��ȡ�ڵ�ģ�;���
    glm::mat4 GetModelMatrix() const;

    // ��Ⱦ�������麯����������ʵ�־������Ⱦ������
    virtual void Render(ThirdCamera& camera, const glm::mat4& model) const;

    // ������Ⱦ����
    void SetRenderable(Renderable* renderable);

    // ���ø��±�־Ϊ
    void SetUpdate(bool flag = true);

    // ��Ҫ����
    bool NeedUpdate()const;

    // ���¾���
    void Update(bool force = false);
    // ���°�Χ�б任
    //void UpdateAABBTransform();

public:
    Node*              m_parent;           // ���ڵ�ָ��
    std::vector<Node*> m_children;         // �ӽڵ�����

    glm::vec3          m_scale;            // ����
    glm::vec3          m_position;         // λ��
    glm::quat          m_rotation;         // ��ת����Ԫ����   
    unsigned           m_flag;             // ��־λ
    AABB               m_aabb;             // AABB��Χ��
                       
    glm::mat4          m_modelMatrix;      // ģ�;���
    Renderable*        m_renderable;       // ����Ⱦ��

   
};
