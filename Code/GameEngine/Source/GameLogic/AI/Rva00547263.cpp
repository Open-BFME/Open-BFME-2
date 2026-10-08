// cl: /ICode/Libraries/Include/Lib /DNDEBUG /MD /EHsc
// ?Rva00547263@@YA_NPAVObject@@PBUCoord3D@@@Z @0x00547263 52B cdecl leaf.
// Evidence: null guard, Object+0x438 bit 0 gate, rowed distance rva002C97E8 from
// Object+0x38 to the second argument, compared against the float constant 20.0
// at 0x007C5CCC. Callers: MoveToGroupOrder family (edge attribution, unproven).
#include "Coord3D.h"

class Object
{
public:
	float rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	char m_pad0[0x38];
	Coord3D m_position; // +0x38
	char m_pad1[0x438 - 0x38 - sizeof(Coord3D)];
	unsigned char m_privateStatus; // +0x438
};

bool Rva00547263(Object *p, const Coord3D *q)
{
	if (p == 0 || (p->m_privateStatus & 1))
		return true;
	return 20.0f > p->rva002C97E8(&p->m_position, q);
}
