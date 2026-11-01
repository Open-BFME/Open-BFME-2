// cl: /DNDEBUG /MD
//
// ?Rva004C20D5IsWithin@@YG_NMPBUCoord3D@@0@Z @0x004C20D5 82B. XY distance check.
// Evidence: free __stdcall ret 0xC with float plus two 12B pointers, 3x movss
// subss plus stores to 12B local, Coord2D GetLength row 0x0000599F on XY part,
// fld plus fcompi plus jb returning AL 1 when dist >= length. Callers 0x004C21A9
// plus self-neighbour. Honest address name.
#include "../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../Libraries/Include/Lib/Coord3D.h"

bool __stdcall Rva004C20D5IsWithin(float dist, const Coord3D *lhs, const Coord3D *rhs)
{
	Coord3D diff;
	diff.x = rhs->x;
	diff.y = rhs->y;
	diff.z = rhs->z;
	diff.x -= lhs->x;
	diff.y -= lhs->y;
	diff.z -= lhs->z;
	float len = ((const Coord2D *)&diff)->GetLength();
	if (dist >= len)
		return true;
	return false;
}
