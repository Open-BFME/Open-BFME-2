// cl: /DNDEBUG /MD /EHsc
// ?rva002E74C6@Pathfinder@@QAEXW4PathfindLayerEnum@@PAVRva001E48E8@@PBUCoord3D@@@Z, retail 0x002E74C6, 124 bytes.
// Sibling of 0x002E7296: floor(world*INV) to cell, then Rva001E48E8::rva001E48E8(table[flags&0xf]).
// Evidence: rowed getCell 0x002E6D62, rowed rva001E48E8 0x001E48E8, IAT floor, INV _INV, ret 0xC.
enum PathfindLayerEnum
{
	LAYER_0 = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class PathfindCell
{
public:
	char m_pad[12];
	int m_flags;
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
	void rva002E74C6(PathfindLayerEnum layer, class Rva001E48E8 *obj, const Coord3D *pos);
};

class Rva001E48E8
{
public:
	void *rva001E48E8(unsigned mask);
};

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern unsigned int g_00DBD33C[];

typedef float Real;

static const Real INV = 1.0f / 10.0f;

static __forceinline Real fast_floor(Real f)
{
	return (Real)floor((double)f);
}

static __forceinline long fast_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

void Pathfinder::rva002E74C6(PathfindLayerEnum layer, Rva001E48E8 *obj, const Coord3D *pos)
{
	int ix = fast_round(fast_floor(pos->x * INV));
	int iy = fast_round(fast_floor(pos->y * INV));
	PathfindCell *cell = getCell(layer, ix, iy);
	unsigned mask;
	if (cell)
		mask = (unsigned)(cell->m_flags & 0xf);
	else
		mask = 0;
	obj->rva001E48E8(g_00DBD33C[mask]);
}
