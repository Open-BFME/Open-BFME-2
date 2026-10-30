// cl: /GX
// ?rva006C0DA0@TaintManagerImpl@@QAEXXZ @ 0x006C0DA0 76B
// Honest address name: thiscall grid iterator over width*height 12B records.
// Evidence: callers at 0x006C1132 and 0x006C0823; neighbours Bfme5SeventySix /GX
// and BfmeGridRasterCircle /GX; imul width*height lea *3 *4 end pointer;
// per-pixel cdecl callback at +0x2c with (x y byte) and 12B stride.
#include "../../../Libraries/Include/Lib/Region3D.h"

typedef float Real;
class BfmeCellFC;
struct BfmePointFC;
class GridXferView;
typedef void (__cdecl *BfmeCellVisitorFC)(int x, int y,
	unsigned char kind);
class TaintManagerImpl
{
public:
	TaintManagerImpl();
	~TaintManagerImpl();
	void SetExtents(const Region3D *region, Real cellSize);
	void rva006C0F50(GridXferView*);
	void rva006C0DA0();
	void _ReallocCells(Region3D region, Real cellSize);
	void bfmeGetCellRange(BfmeCellFC **first, BfmeCellFC **last,
		int x1, int x2, int y);
	void ChangeTaintLevel(int x, int y, int radius, int amount, bool absolute, int mode);
	BfmeCellFC *bfmeCellAtWorld(Real worldX, Real worldY) const;
	int rva006C0E40(const BfmePointFC *point, int *extra);
	BfmeCellFC *rva006C0C60(int x, int y);
	int rva006C0DF0(int x, int y, int *extra);
	int rva006C0E70(int x, int y);
	int rva006C0EB0(const BfmePointFC *point) const;
	int rva006C0860(Real worldX) const;
	int rva006C0890(Real worldY) const;
	int rva006C08C0(Real distance) const;

	friend class BfmeRangeUpdaterFC;
	friend class BfmeTaintManager;

private:
	Region3D m_bfmeRegion;					// +0x00
	Real m_bfmeCellSize;					// +0x18
	float m_bfmeCellSizeInv;				// +0x1C
	int m_bfmeWidth;					// +0x20
	int m_bfmeHeight;					// +0x24
	BfmeCellFC *m_bfmeCells;				// +0x28
	BfmeCellVisitorFC m_bfmeVisitor;			// +0x2C
};
void TaintManagerImpl::rva006C0DA0()
{
	unsigned char *end = (unsigned char *)m_bfmeCells + (m_bfmeHeight * m_bfmeWidth * 3) * 4;
	unsigned char *p = (unsigned char *)m_bfmeCells;
	int x = 0;
	int y = 0;
	if (p == end)
		return;
	do {
		int v = *p;
		m_bfmeVisitor(x, y, v);
		if (++x == m_bfmeWidth) {
			x = 0;
			++y;
		}
		p += 12;
	} while (p != end);
}
