// cl: /DNDEBUG /MD /EHsc
// ?Rva002E7875WorldToCell@@YAPAUICoord2D@@PAU1@_NPBUCoord3D@@@Z @0x002E7875 162B
// Free world-to-cell converter used by Pathfinder clamp/validate callers
// (0x002E7917 0x002E7964 read this+0x14/0x18/0x1c/0x20 as m_extent).
// Donor pattern: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/
// Rva003F8820Pathfinder.cpp REAL_TO_INT_FLOOR and PathfinderObjectCell.cpp
// centerInCell floor vs floor+0.5. Scale 0.1 at 0x7C2424, half 0.5 at 0x7C26F0.
// Inline asm fld/fistp in fast_round avoids _ftol so the CRT floor narrow plus
// fld/fistp pair matches retail x87 shape.

typedef int Int;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

static const Real INV = 1.0f / 10.0f;

extern "C" __declspec(dllimport) double __cdecl floor(double);

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

#define R2I(x) (fast_round(fast_floor(x)))

ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
{
	int ix;
	int iy;
	if (center) {
		ix = R2I(pos->x * INV);
		iy = R2I(pos->y * INV);
	} else {
		ix = R2I(pos->x * INV + 0.5f);
		iy = R2I(pos->y * INV + 0.5f);
	}
	out->x = ix;
	out->y = iy;
	return out;
}
