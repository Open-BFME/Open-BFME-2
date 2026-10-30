// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?rva0073BB40@Rva0073BAA0Base@@QAEDHHH@Z @0x0073BB40 159B: shroud range updater decrement twin of 0x0073BAA0.
// Donor mask-loop shape from reference/open-bfme-1/Code/GameEngine/Source/Common/BfmeConv1561.cpp
// BfmeShroudVRA::bfmeUpdateVRA plus volatile-first pattern from taintmanager_impl.cpp BfmeRangeUpdaterFC;
// range via rowed ?rva0073A2A0@Gen_008F7CD0@@QAEXPAPAVBfmeCellFD@@0HHH@Z (BfmeCellAt.cpp, 0xA8 stride),
// per-cell gate is own vtable slot 0 testFunc(x y), per-player update is the rowed 008FC3B0 variant.
// Callers 0x0073C3B0 0x0073C450 0x0073C7C0 pass grid as +4 mask as +8; this+0 is vtable, +4 grid, +8 mask.
// Returns 1 always; ret 0xc is (x1 x2 y).
class BfmeCellFD;
class ShroudManagerImpl;
class ShroudManagerCell;

class Gen_008F7CD0
{
public:
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int x1, int x2, int y);
};

class ShroudManagerCell
{
public:
	void updatePlayerCells008FC3B0(ShroudManagerImpl *manager, int playerIndex);
};

class Rva0073BAA0Base
{
public:
	Rva0073BAA0Base(Gen_008F7CD0 *grid, unsigned int mask);
	virtual char testFunc(int x, int y);
	char rva0073BB40(int minX, int maxX, int cellY);
private:
	Gen_008F7CD0 *m_grid;
	unsigned int m_mask;
};

char Rva0073BAA0Base::rva0073BB40(int minX, int maxX, int cellY)
{
	BfmeCellFD *volatile first;
	BfmeCellFD *last;
	m_grid->rva0073A2A0((BfmeCellFD **)&first, &last, minX, maxX, cellY);
	unsigned int mask = m_mask;
	int index = 0;
	if (mask != 0)
	{
		BfmeCellFD *end = last;
		do
		{
			if ((mask & 1) != 0)
			{
				BfmeCellFD *cell = first;
				int cellX = minX;
				if (cell != end)
				{
					do
					{
						if (testFunc(cellX, cellY))
							((ShroudManagerCell *)cell)->updatePlayerCells008FC3B0(
								(ShroudManagerImpl *)m_grid, index);
						++cellX;
						cell = (BfmeCellFD *)((char *)cell + 0xA8);
					} while (cell != end);
				}
			}
			mask >>= 1;
			++index;
		} while (mask != 0);
	}
	return 1;
}

// Native inverse circle constructs CF139C, the same12-byte base view
// used by reveal. Rectangle CE30 instead passes CF13A4 with extra4.
// The base predicate remains owned once at188170; original types unknown.

// ??0Rva0073BAA0Base@@QAE@PAVGen_008F7CD0@@I@Z @0x0073B470 25B (RET 8): the
// out-of-line constructor of this 12-byte updater base: vtable 0x00CF139C,
// grid at +4, mask at +8 -- the same stores the reveal and rectangle callers
// make inline. Address-derived class name kept.
Rva0073BAA0Base::Rva0073BAA0Base(Gen_008F7CD0 *grid, unsigned int mask) : m_grid(grid), m_mask(mask)
{
}

// ??0Rva0073BAA0@@QAE@PAVGen_008F7CD0@@IH@Z @0x0073B4E0 32B and
// ??0Rva0073BB40@@QAE@PAVGen_008F7CD0@@IH@Z @0x0073B500 32B (RET 0xC): the
// out-of-line constructors of the two derived updaters (vtables 0x00CF13A0
// and 0x00CF13A4) over the base above, each adding its extra word at +0xC.
// Class names follow Rva0073CE30.cpp, which builds the same two inline.
class Rva0073BAA0 : public Rva0073BAA0Base
{
public:
	Rva0073BAA0(Gen_008F7CD0 *grid, unsigned int mask, int extra);
private:
	int m_extra;
};

Rva0073BAA0::Rva0073BAA0(Gen_008F7CD0 *grid, unsigned int mask, int extra) : Rva0073BAA0Base(grid, mask), m_extra(extra)
{
}

class Rva0073BB40 : public Rva0073BAA0Base
{
public:
	Rva0073BB40(Gen_008F7CD0 *grid, unsigned int mask, int extra);
private:
	int m_extra;
};

Rva0073BB40::Rva0073BB40(Gen_008F7CD0 *grid, unsigned int mask, int extra) : Rva0073BAA0Base(grid, mask), m_extra(extra)
{
}
