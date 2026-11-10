// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?Rva0073C7C0Fill@@YADHHHHVRva0073BB40@@@Z @0x0073C7C0 83B: shroud rect fill via rowed 0x0073BB40.
// Normalizes (x1 x2) and (y1 y2) with swaps then sweeps y calling the decrement updater per row;
// 0 on first row failure 1 on full sweep. Caller 0x0073CE84 in 0x0073CE30; twin of the 0x0073BF40 circle
// family but rect (no midpoint state). Updater is Rva0073BB40 by value (16B: base12 plus derived extra4).
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

class Rva0073BB40 : public Rva0073BAA0Base { int extra; };

char __cdecl Rva0073C7C0Fill(int x1, int x2, int y1, int y2, Rva0073BB40 updater)
{
	if (x1 > x2)
	{
		int tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2)
	{
		int tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	for (int y = y1; y <= y2; ++y)
	{
		if (!updater.rva0073BB40(x1, x2, y))
			return 0;
	}
	return 1;
}

// Native inverse circle constructs CF139C, the same12-byte base view
// used by reveal. Rectangle CE30 instead passes CF13A4 with extra4.
// The base predicate remains owned once at188170; original types unknown.
