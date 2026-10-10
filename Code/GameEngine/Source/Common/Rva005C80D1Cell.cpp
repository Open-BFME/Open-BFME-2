// cl: /O1 /G7 /arch:SSE /MD
// ?Rva005C80D1Cell@@YAXPBURva005C80D1Origin@@PBURva005C80D1Point@@MPAH2@Z
//
// ?Rva005C80D1Cell@@YAXPBURva005C80D1Origin@@PBURva005C80D1Point@@MPAH2@Z, retail 0x005C80D1 (138 bytes, cdecl).
// Owner and meaning unproven: maps a point to the cell indices of a grid origin (+0x08/+0x0C) at a cell size,
// rounding up (origin - point) / size on each axis. The ceil reaches the CRT import (msvcr71!ceil, 0x00BBA578) and the float-to-int store is
// the fistp the tree's own helpers use (Bfme5SeventySix.cpp's bfmeFloatToLongFC).
typedef float Real;

#include <math.h>

__forceinline Real Rva005C80D1Ceil(Real value)
{
	return ceil(value);
}

__forceinline long Rva005C80D1ToLong(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

struct Rva005C80D1Origin
{
	char m_pad00[8];
	Real m_08;
	Real m_0c;
};

struct Rva005C80D1Point
{
	Real x;
	Real y;
};

void Rva005C80D1Cell(const Rva005C80D1Origin *origin, const Rva005C80D1Point *point, Real cellSize, int *cellX, int *cellY)
{
	Real inverse = 1.0f / cellSize;
	*cellX = Rva005C80D1ToLong(Rva005C80D1Ceil((origin->m_08 - point->x) * inverse));
	*cellY = Rva005C80D1ToLong(Rva005C80D1Ceil((origin->m_0c - point->y) * inverse));
}
