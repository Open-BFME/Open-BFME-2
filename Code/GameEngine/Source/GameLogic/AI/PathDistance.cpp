// cl: /DNDEBUG /MD
#include <math.h>

// ?Rva00363CF3Distance@@YANPBUCoord3D@@0@Z, retail 0x00363CF3, 45 bytes.
// 2D distance between two positions via sqrt(dx*dx+dy*dy). Callers pass
// PathNode positions (+0xC) in 0x00363D74 and 0x003642DF; callee is the
// sqrt import thunk at 0x0062921C. x87 shape with push-ecx double temp
// matches retail; gate fills the call relocation.

struct Coord3D
{
	float x;
	float y;
	float z;
};

double __cdecl Rva00363CF3Distance(const Coord3D *a, const Coord3D *b)
{
	float dx = a->x - b->x;
	float dy = a->y - b->y;
	return sqrt(dx * dx + dy * dy);
}
