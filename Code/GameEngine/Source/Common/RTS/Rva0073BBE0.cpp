// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?rva0073BBE0@Rva0073BBE0@@QAEDHHH@Z @0x0073BBE0 117B: shroud range adjust sibling of 0x0073BAA0.
// Same mask-loop shape as Rva0073BAA0.cpp but no per-cell predicate; per-cell work is the rowed
// adjustPlayerCounter008FC1F0 variant with (index m+8 m+0xC). Grid at +0 mask at +4.
// Callers 0x0073C820 pass grid as +0 mask as +4; returns 1 always; ret 0xc is (x1 x2 y).
class BfmeCellFD;
class ShroudManagerCell;

#include "../../../Include/Common/Gen_008F7CD0.h"

#include "../../../Include/Common/ShroudManagerCell.h"

class Rva0073BBE0
{
public:
	char rva0073BBE0(int x1, int x2, int y);
private:
	Gen_008F7CD0 *m_grid;
	unsigned int m_mask;
	int m_counterIndex;
	int m_amount;
};

char Rva0073BBE0::rva0073BBE0(int x1, int x2, int y)
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
				if (cell != end)
				{
					do
					{
						((ShroudManagerCell *)cell)->adjustPlayerCounter008FC1F0(
							index, m_counterIndex, m_amount);
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
