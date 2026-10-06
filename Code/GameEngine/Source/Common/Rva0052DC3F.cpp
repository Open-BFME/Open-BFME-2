// cl: /DNDEBUG /MD
// ?rva0052DC3F@Rva0052DC3F@@QAEHPBURva0052DC3FArg@@@Z, retail 0x0052DC3F, 88 bytes.
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

struct Rva0052DC3FArg
{
	Rva0052DC3FPoint *m_0;
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

class Rva0052DC3F
{
public:
	int rva0052DC3F(const Rva0052DC3FArg *a);
private:
	Rva0052DC3FPoint *m_0;
};

int Rva0052DC3F::rva0052DC3F(const Rva0052DC3FArg *a)
{
	int dx = m_0->x - a->m_0->x;
	int dy = m_0->y - a->m_0->y;
	int d2 = dy * dy + dx * dx;
	double f = floor(sqrt((double)d2) * g_Va00BC2428 + g_Va00BC26F0);
	return fast_round((Real)f);
}
// ?g_Va00BC26F0@@3MA: the global at VA 0xbc26f0 is ?g_Va007C26F0@@3MA.
#pragma comment(linker, "/alternatename:?g_Va00BC26F0@@3MA=?g_Va007C26F0@@3MA")
