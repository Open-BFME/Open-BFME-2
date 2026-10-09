// cl: /MD
//
// ?rva001E3557@Rva001E3557@@QAE_NXZ @0x001E3557 (58B).
// Guarded bool check sibling of 0x001E3591: +4 set plus +0x10 object
// runs rowed 0x363BC7 into Coord2D plus len locals then true when
// g_Va00BC2428 > len. Evidence: callee row 0x363BC7 plus global
// 0x00BC2428 plus caller 0x1E9157 in 0x1E9083.

extern float g_Va00BC2428;

#include "../../../Libraries/Include/Lib/Coord2D.h"

class Rva00363BC7
{
public:
	void *rva00363BC7(Coord2D *out, float *outLen);
};

class Rva001E3557
{
public:
	bool rva001E3557();
private:
	int m_pad00;
	int m_p04;
	int m_pad08[2];
	Rva00363BC7 *m_p10;
};

bool Rva001E3557::rva001E3557()
{
	if (m_p04 == 0)
		return false;
	Rva00363BC7 *p = m_p10;
	if (p == 0)
		return false;
	Coord2D out;
	float len;
	if (p->rva00363BC7(&out, &len) == 0)
		return false;
	if (g_Va00BC2428 > len)
		return true;
	return false;
}
