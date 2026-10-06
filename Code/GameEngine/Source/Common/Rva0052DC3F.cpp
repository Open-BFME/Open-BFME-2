// cl: /DNDEBUG /MD
// PathfindCell::CalcCostToHierGoal, retail 0x0052DC3F, 88 bytes (WorldBuilder name,
// pathfinder_cell.cpp line 370: the same sqrt/floor cost between this cell and the
// goal cell through their +0 pointers).
// Integer 2D distance with sqrt scale floor and fistp return. this+0 holds point,
// arg+0 holds point, each point has int x at +0 y at +4. dx*dx+dy*dy via imul,
// sqrt thunk at 0x0062921C, scale 10.0f at 0x00BC2428 bias at 0x00BC26F0,
// floor via IAT, fistp via fast_round to avoid _ftol (x87 blocker precedent
// PathfindShimWorldToCell.cpp). Evidence: unlocks 0x002F5022; callers push one
// arg plus ecx (thiscall) with ret 4; prev 0x0052DC29 next 0x0052DD41.
#include <math.h>

typedef float Real;

struct Rva0052DC3FPoint
{
	int x;
	int y;
};

extern float g_Va00BC2428;
extern float g_Va00BC26F0;

extern "C" __declspec(dllimport) double __cdecl floor(double);

static __forceinline long fast_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class PathfindCell
{
public:
	int CalcCostToHierGoal(PathfindCell *goal);
private:
	Rva0052DC3FPoint *m_0;
};

int PathfindCell::CalcCostToHierGoal(PathfindCell *goal)
{
	int dx = m_0->x - goal->m_0->x;
	int dy = m_0->y - goal->m_0->y;
	int d2 = dy * dy + dx * dx;
	double f = floor(sqrt((double)d2) * g_Va00BC2428 + g_Va00BC26F0);
	return fast_round((Real)f);
}
// ?g_Va00BC26F0@@3MA: the global at VA 0xbc26f0 is ?g_Va007C26F0@@3MA.
#pragma comment(linker, "/alternatename:?g_Va00BC26F0@@3MA=?g_Va007C26F0@@3MA")
