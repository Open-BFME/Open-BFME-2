// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000CBA20Point
{
public:
	float x;
	float y;
};

#include "RTS/XYDistanceCallView.h"


float Rva000CBA20::distSq(const Rva000CBA20Point *p)
{
	float dx = m_x - p->x;
	float dy = m_y - p->y;
	return dx * dx + dy * dy;
}
