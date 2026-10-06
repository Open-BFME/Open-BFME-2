// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?Rva0073BF40Raster@@YADHHHVRva0073BAA0@@@Z @0x0073BF40 155B: shroud circle raster via rowed 0x0073BAA0 updater.
// Midpoint-circle shape from reference/open-bfme-1/Code/Libraries/Source/taintmanager/taintmanager_impl.cpp
// bfmeRasterCircleFC (donor void __cdecl with BfmeRangeUpdaterFC by value); target is the shroud twin:
// char __cdecl with Rva0073BAA0 updater by value, per-row gate is the rowed rva0073BAA0 testFunc updater,
// checked (test al fail) with 1 on full sweep 0 on early out; ret 0 is (centerX centerY radius updater).
// Caller 0x0073CB5A builds the 0x008F139C updater temp; unblocks 0x0073CAF0.
class BfmeCellFD;

class Gen_008F7CD0
{
public:
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int x1, int x2, int y);
};

class ShroudManagerImpl;
class ShroudManagerImpl008FBA40Element;

class Rva0073BAA0
{
public:
	virtual char testFunc(int x, int y);
	char rva0073BAA0(int x1, int x2, int y);
private:
	Gen_008F7CD0 *m_grid;
	unsigned int m_mask;
};

char __cdecl Rva0073BF40Raster(int centerX, int centerY, const int radius, Rva0073BAA0 updater)
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

			if (!updater.rva0073BAA0(firstX, lastX, centerY + y))
				return 0;
			if (y == 0)
				return 1;

			if (!updater.rva0073BAA0(firstX, lastX, centerY - y))
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
