// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?rva0073BB40@Rva0073BB40@@QAEDHHH@Z @0x0073BB40 159B: shroud range updater decrement twin of 0x0073BAA0.
// Donor mask-loop shape from reference/open-bfme-1/Code/GameEngine/Source/Common/BfmeConv1561.cpp
// BfmeShroudVRA::bfmeUpdateVRA plus volatile-first pattern from taintmanager_impl.cpp BfmeRangeUpdaterFC;
// range via rowed ?rva0073A2A0@Gen_008F7CD0@@QAEXPAPAVBfmeCellFD@@0HHH@Z (BfmeCellAt.cpp, 0xA8 stride),
// per-cell gate is own vtable slot 0 testFunc(x y), per-player update is the rowed 008FC3B0 variant.
// Callers 0x0073C3B0 0x0073C450 0x0073C7C0 pass grid as +4 mask as +8; this+0 is vtable, +4 grid, +8 mask.
// Returns 1 always; ret 0xc is (x1 x2 y).
class BfmeCellFD;
class ShroudManagerImpl;
class ShroudManagerImpl008FBA40Element;

class Gen_008F7CD0
{
public:
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int x1, int x2, int y);
};

class ShroudManagerImpl008FBA40Element
{
public:
	void updatePlayerCells008FC3B0(ShroudManagerImpl *manager, int playerIndex);
};

class Rva0073BB40
{
public:
	virtual char testFunc(int x, int y);
	char rva0073BB40(int x1, int x2, int y);
private:
	Gen_008F7CD0 *m_grid;
	unsigned int m_mask;
};

char Rva0073BB40::rva0073BB40(int x1, int x2, int y)
{
	BfmeCellFD *volatile first;
	BfmeCellFD *last;
	m_grid->rva0073A2A0((BfmeCellFD **)&first, &last, x1, x2, y);
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
				int x = x1;
				if (cell != end)
				{
					do
					{
						if (testFunc(x, y))
							((ShroudManagerImpl008FBA40Element *)cell)->updatePlayerCells008FC3B0(
								(ShroudManagerImpl *)m_grid, index);
						++x;
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
