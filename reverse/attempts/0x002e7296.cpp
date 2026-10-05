// ?rva002E7296@Pathfinder@@QAEEW4PathfindLayerEnum@@PBXPBM@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva002E7296@Pathfinder@@QAEEW4PathfindLayerEnum@@PBXPBM@Z, retail 0x002E7296, 158 bytes.
// Thiscall predicate over Pathfinder::getCell: floor(world*INV) to cell,
// true for low4 4/5/0 (with 0x3f0==0x10 gate), else table[low]&objbits.
// Evidence: rowed getCell 0x002E6D62, IAT floor, INV _INV, ret 0xC, callers.
enum PathfindLayerEnum
{
	LAYER_0 = 0
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
	unsigned char rva002E7296(PathfindLayerEnum layer, const void *obj, const float *pos);
};

extern "C" float INV;
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern unsigned int g_00DBD33C[];

typedef float Real;

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

// ?rva002E7296@Pathfinder@@QAEEW4PathfindLayerEnum@@PBXPBM@Z present-unmatched
unsigned char Pathfinder::rva002E7296(PathfindLayerEnum layer, const void *obj, const float *pos)
{
	int ix = fast_round(fast_floor(INV * pos[0]));
	int iy = fast_round(fast_floor(INV * pos[1]));
	PathfindCell *cell = getCell(layer, ix, iy);
	if (!cell)
		return (unsigned char)0;
	int low = cell->m_flags & 0xf;
	int flags = cell->m_flags;
	if (low == 4)
		return (unsigned char)1;
	if (low == 5)
		return (unsigned char)1;
	if ((flags & 0x3f0) == 0x10)
		goto checkObj;
	if (low == 0)
		return (unsigned char)1;
checkObj:
	unsigned int bits = *(unsigned int *)((const char *)*(void *const *)((const char *)obj + 4) + 0x14);
	return (unsigned char)((bits & g_00DBD33C[low]) != 0);
}
