// Retail 00311F46/156B, Ghidra boundary; caller 003767BB and sibling vector operations.
// Clean BFME1 9cbfb551fe20 Rva003A2270Find.cpp guides the loop and 184-byte records.
// Target facts: +2C vector, +A4 triple, skip first/last two, XY threshold and copied hit.
// The concrete owner remains unknown; the name is target-address-derived.
// BFME2 uses the rowed Coord3D::length, including a zero third coordinate.
// Delaying that zero until after subtraction reproduces the independent SSE X/Y values.
// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
typedef float Real;
typedef bool Bool;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct Rva00311F46Delta
{
	// ?Rva00311F46Delta::Rva00311F46Delta present-unmatched
	Rva00311F46Delta(Real initialX, Real initialY)
		: x(initialX), y(initialY) {}

	Real x;
	Real y;
	Real unused;

	// ?Rva00311F46Delta::length present-unmatched
	Real length() const
	{
		return ((const Coord3D*)this)->length();
	}
};

struct Rva00311F46Element
{
	char pad00[0xa4];
	Coord3D point;
	char padb0[8];
};

class Rva00311F46
{
public:
	Bool find(const Coord3D &position, Real distance);

private:
	char pad00[0x2c];
	_STL::vector<Rva00311F46Element> entries;
};

Bool Rva00311F46::find(const Coord3D &position, Real distance)
{
	for (Rva00311F46Element *it = entries.begin() + 2;
		it != entries.end(); ++it)
	{
		if (it == entries.begin() + entries.size() - 2)
			return false;
		Rva00311F46Delta delta(it->point.x, it->point.y);
		delta.x -= position.x;
		delta.y -= position.y;
        delta.unused=0.0f;
		if (delta.length() < distance)
		{
			it->point = position;
			return true;
		}
	}
	return false;
}
