// cl: /O2 /Ob0 /G6

struct BfmeCoordEB
{
	float m_x;
	float m_y;
	float m_z;
};

#include "../../Include/Common/Geometry.h"

class BfmeObjEB
{
public:
	unsigned char m_pad[0x44];
	BfmeCoordEB m_44;
	BfmeCoordEB m_50;
};

void bfmeApplyEB(BfmeObjEB *obj)
{
	BfmeCoordEB offset;
	offset.m_x = 0.0f;
	offset.m_y = 0.0f;
	offset.m_z = ((GeometryInfo *)obj)->getMaxHeightAbovePosition() * 0.67f;
	obj->m_50 = offset;
	if (obj->m_44.m_z < offset.m_z)
		obj->m_44 = offset;
}
