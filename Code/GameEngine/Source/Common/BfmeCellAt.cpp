// BFME1 Bfme5SeventySeven.cpp row-major lookup adapted to target stride.
// Donor labels are provisional; target 0x73BD70 directly calls this lookup.
// The cell record is incomplete here: retail evidence establishes its 0xA8 stride,
// but this function only returns its address.
// cl: /O2 /DNDEBUG /MD
class BfmeCellFD;

class Gen_008F7CD0
{
public:
	BfmeCellFD *bfmeAt(int x, int y) const;

private:
	char m_bfmeHead[0x24];
	int m_bfmeWidth;
	int m_bfmeHeight;
	BfmeCellFD *m_bfmeCells;
};

BfmeCellFD *Gen_008F7CD0::bfmeAt(int x, int y) const
{
	if (x < 0 || x >= m_bfmeWidth || y < 0 || y >= m_bfmeHeight)
		return 0;

	unsigned char *base = reinterpret_cast<unsigned char *>(m_bfmeCells);
	return reinterpret_cast<BfmeCellFD *>(base + (y * m_bfmeWidth + x) * 0xA8);
}
