// cl: /DNDEBUG /MD
//
// ?Rva004C20D5IsWithin@@YG_NMPBUCoord3D@@0@Z @0x004C20D5 82B. XY distance check.
// Evidence: free __stdcall ret 0xC with float plus two 12B pointers, 3x movss
// subss plus stores to 12B local, Coord2D GetLength row 0x0000599F on XY part,
// fld plus fcompi plus jb returning AL 1 when dist >= length. Callers 0x004C21A9
// plus self-neighbour. Honest address name.
struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord2D
{
	float GetLength() const;
	float x;
	float y;
};

struct Coord3D : public Coord3DBase
{
};

bool __stdcall Rva004C20D5IsWithin(float dist, const Coord3D *a, const Coord3D *b)
{
	Coord3D diff;
	diff.x = b->x;
	diff.y = b->y;
	diff.z = b->z;
	diff.x -= a->x;
	diff.y -= a->y;
	diff.z -= a->z;
	float len = ((const Coord2D *)&diff)->GetLength();
	if (dist >= len)
		return true;
	return false;
}
