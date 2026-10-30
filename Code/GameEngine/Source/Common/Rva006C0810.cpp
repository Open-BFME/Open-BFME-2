// cl: /MD
// ?rva006C0810@Rva006C0810@@QAEXPBURegion3D@@M@Z @ 0x006C0810 8B
// Honest address name: tail jmp loading member at +0x10 then jumping to rowed
// TaintManagerImpl::SetExtents. Same (const Region3D*, float) signature forwards.
// Evidence: mov ecx [ecx+0x10] plus jmp shape, callee row in Bfme5SeventySix.cpp,
// callers at 0x0024406E and 0x00246D81, neighbours 0x006C0800 and 0x006C0820.
// /O2: frameless float-arg tail jmp; /O1 emits fld/fstp plus call.
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
class Rva006C0810
{
public:
	void rva006C0810(const Region3D *region, float cellSize);
private:
	char m_pad[0x10];
	TaintManagerImpl *m_ptr;
};
void Rva006C0810::rva006C0810(const Region3D *region, float cellSize)
{
	m_ptr->SetExtents(region, cellSize);
}
