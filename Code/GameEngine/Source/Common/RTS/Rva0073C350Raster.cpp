// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?Rva0073C350Raster@@YADHHHHVRva0073BAA0@@@Z @0x0073C350 83B: shroud rect raster via rowed 0x0073BAA0 updater.
// Swaps x1 x2 plus y1 y2 then per-row gate is rowed rva0073BAA0 testFunc updater
// checked (test al fail) with 1 on full sweep 0 on early out; ret 0 is (x1 x2 y1 y2 updater).
// Precedent Rva0073BF40Raster.cpp circle twin; caller 0x0073CCB4 passes 4 ftol ints.
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

char __cdecl Rva0073C350Raster(int x1, int x2, int y1, int y2, Rva0073BAA0 updater)
{
	if (x1 > x2)
	{
		int t = x1;
		x1 = x2;
		x2 = t;
	}
	if (y1 > y2)
	{
		int t = y1;
		y1 = y2;
		y2 = t;
	}
	for (int y = y1; y <= y2; ++y)
	{
		if (!updater.rva0073BAA0(x1, x2, y))
			return 0;
	}
	return 1;
}
