#include "Entity.h"

class Box:public Entity
{
public:
	Box()
	{

	};
	~Box() {

	};

	virtual void  Render(const Camera &camera )
	{

	};
private:
	unsigned  m_vao;
	unsigned  m_vbo;
	unsigned  m_ebo;

};
