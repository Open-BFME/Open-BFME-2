// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?Rva0073C3B0Raster@@YADHHHVRva0073BAA0Base@@@Z @0x0073C3B0 155B: shroud circle raster decrement twin via rowed 0x0073BB40.
// Same midpoint-circle shape as 0x0073BF40 (donor taintmanager_impl.cpp bfmeRasterCircleFC);
// per-row gate is the rowed rva0073BB40 decrement updater, checked with 1 on full sweep 0 on early out.
// Caller 0x0073CD2A; unblocks 0x0073CCC0.
class BfmeCellFD;

#include "../../../Include/Common/Gen_008F7CD0.h"

class ShroudManagerImpl;
class ShroudManagerCell;

class Rva0073BAA0Base
{
public:
	virtual char testFunc(int x, int y);
	char rva0073BB40(int x1, int x2, int y);
private:
	Gen_008F7CD0 *m_grid;
	unsigned int m_mask;
};

char __cdecl Rva0073C3B0Raster(int centerX, int centerY, const int radius, Rva0073BAA0Base updater)
{
	int x = 0;
	int y = radius;
	int d = (1 - radius) << 1;
	int firstX = centerX;
	int lastX = centerX;

	for (;;)
	{
		if (d + y > 0)
		{
			if (y == 0 && radius == 1)
			{
				++x;
				++lastX;
				--firstX;
			}

			if (!updater.rva0073BB40(firstX, lastX, centerY + y))
				return 0;
			if (y == 0)
				return 1;

			if (!updater.rva0073BB40(firstX, lastX, centerY - y))
				return 0;
			--y;
			d -= ((y << 1) - 1);
		}

		if (x > d)
		{
			++x;
			++lastX;
			--firstX;
			d += ((x << 1) + 1);
		}
	}
}

// Native inverse circle constructs CF139C, the same12-byte base view
// used by reveal. Rectangle CE30 instead passes CF13A4 with extra4.
// The base predicate remains owned once at188170; original types unknown.
