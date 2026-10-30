// cl: /GX /ICode/Libraries/Include

// ?bfmeResetGrid@BfmeTaintManager@@UAEXXZ
//
// BFME1 donor Bfme5SeventySix.cpp shape: reset the owned grid, then
// re-establish it over an empty region. BFME2 repair: the grid pointer sits
// at +0x10 here, not BFME1's +0x0C (near-miss drift at +0x08: mov ecx,
// [esi+0x0C] vs [esi+0x10]). B1 0x00881070 82B -> B2 0x006C0A50 82B,
// immediate-only drift. The grid reset itself is the empty fold at
// 0x0069E440 (pin); SetRegion resolves via pin at 0x006C1500.

typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

__forceinline Real bfmeFloatFloorFC(Real value)
{
	return (Real)floor((double)value);
}

__forceinline Real bfmeFloatCeilFC(Real value)
{
	return (Real)ceil((double)value);
}

__forceinline long bfmeFloatToLongFC(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

struct BfmePointFC
{
	Real x;
	Real y;
};

#include "Lib/Coord3D.h"

// Zero Hour's inline Coord3D::zero, expanded in place as in retail. A unit-local
// inline member emitted a /GX COMDAT for ?zero@Coord3D@@QAEXXZ that is not
// retail's coord3d.cpp owner at 0x0000366B.
__forceinline void bfmeZeroCoord3D(Coord3D &coord)
{
	coord.x = 0.0f;
	coord.y = 0.0f;
	coord.z = 0.0f;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../Libraries/Include/Lib/Region3D.h"

class BfmeCellFC
{
public:
	BfmeCellFC();
	~BfmeCellFC();

	unsigned char m_bfmeKind;				// +0x00
	unsigned char m_bfmeGap[3];				// +0x01
	int m_bfmeValue;					// +0x04
	// Retail ??1TaintManagerImpl passes element size 12 to the vector
	// destructor helper, so BFME2 cells carry one more word than BFME1's
	// 8-byte cells. No landed body reads it yet; purpose unestablished.
	int m_bfmeExtra;					// +0x08
};

typedef void (__cdecl *BfmeCellVisitorFC)(int x, int y,
	unsigned char kind);

// MSVC 7.1 folds `delete []` onto the scalar ??3@YAXPAX@Z unless the array
// form is declared where it can see it; retail calls ??_V@YAXPAX@Z here
// (rowed, mem_ops.cpp).
void operator delete[]( void *block );

class GridXferView;

// Retail calls an empty grid method here that /OPT:ICF folded onto a shared
// empty body (0x0069E440, rowed as an STL destructor). Its pin predates the
// class name and that address cannot take a second spelling, so the calls
// keep the pinned name through this one-method view.
class Gen_008812D0
{
public:
	void bfmeReset();
};

class TaintManagerImpl
{
public:
	void SetExtents(const Region3D *region, Real cellSize);
	void _ReallocCells(Region3D region, Real cellSize);
	void ChangeTaintLevel(int x, int y, int radius, int amount, bool absolute, int mode);
	int rva006C0E40(const BfmePointFC *point, int *extra);
	int rva006C0E70(int x, int y);
	void rva006C0F50(GridXferView *xfer);
	~TaintManagerImpl();

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

class BfmeTaintManager
{
public:
	virtual void bfmeResetGrid();
	void bfmeApplyCircleWorld(const BfmePointFC *point, Real radius, int amount, bool absolute, int mode);
	int rva006C0850(const BfmePointFC *point, int *extra);
	unsigned char rva006C0840(int cellX, int cellY);
	void rva006C07F0();

private:
	unsigned char m_bfmeHead[0x10 - 4];				// +0x04
	TaintManagerImpl *m_bfmeGrid;				// +0x10
};

// ?bfmeResetGrid@BfmeTaintManager@@UAEXXZ
void BfmeTaintManager::bfmeResetGrid()
{
	((Gen_008812D0 *)m_bfmeGrid)->bfmeReset();

	Region3D region;
	bfmeZeroCoord3D(region.lo);
	bfmeZeroCoord3D(region.hi);
	m_bfmeGrid->SetExtents(&region, 0.0f);
}

// ?SetExtents@TaintManagerImpl@@QAEXPBURegion3D@@M@Z
void TaintManagerImpl::SetExtents(const Region3D *region, Real cellSize)
{
	if (cellSize <= 0.0f)
		cellSize = m_bfmeCellSize;

	if (!(region->width() < 0.0f)
		&& !(region->height() < 0.0f))
	{
		_ReallocCells(*region, cellSize);
	}
}

// ??1TaintManagerImpl@@QAE@XZ at retail 0x006C0D70 (39B). Near-miss drift is a
// single literal: push 0x0C (BFME1 pushes 0x08) -- the array-delete helper
// takes the element size, so BFME2 cells are 12 bytes (see BfmeCellFC).
// B1 0x008813E0 -> B2 0x006C0D70, immediate-only drift.
TaintManagerImpl::~TaintManagerImpl()
{
	delete[] m_bfmeCells;
}

// Retail 0x006C0AB0 170B, chain from ChangeTaintLevel: world-to-cell via
// ceil/floor and cellSizeInv, then grid paint with trailing mode word.
void BfmeTaintManager::bfmeApplyCircleWorld(const BfmePointFC *point, Real radius, int amount, bool absolute, int mode)
{
	int cellRadius = bfmeFloatToLongFC(bfmeFloatCeilFC(radius * m_bfmeGrid->m_bfmeCellSizeInv));
	int y = bfmeFloatToLongFC(bfmeFloatFloorFC((point->y - m_bfmeGrid->m_bfmeRegion.lo.y) * m_bfmeGrid->m_bfmeCellSizeInv));
	int x = bfmeFloatToLongFC(bfmeFloatFloorFC((point->x - m_bfmeGrid->m_bfmeRegion.lo.x) * m_bfmeGrid->m_bfmeCellSizeInv));
	m_bfmeGrid->ChangeTaintLevel(x, y, cellRadius, amount, absolute, mode);
}

// ?rva006C0850@BfmeTaintManager@@QAEHPBUBfmePointFC@@PAH@Z @ 0x006C0850 8B
// Honest address name: tail-jmp thunk loading grid at +0x10 then jumping to
// rowed TaintManagerImpl::rva006C0E40. Same (point extra) signature forwards.
// Evidence: chain from 0x006C0E40 landing, mov ecx [ecx+0x10] plus jmp shape,
// BfmeTaintManager grid at +0x10, callers in 0x0049B98A.
int BfmeTaintManager::rva006C0850(const BfmePointFC *point, int *extra)
{
	return m_bfmeGrid->rva006C0E40(point, extra);
}

// ?rva006C0840@BfmeTaintManager@@QAEEHH@Z @ 0x006C0840 8B
// Honest address name: tail-jmp thunk loading grid at +0x10 then jumping to
// rowed TaintManagerImpl::rva006C0E70. Same (x y) signature forwards.
// Evidence: chain from 0x006C0E70 landing, mov ecx [ecx+0x10] plus jmp shape,
// BfmeTaintManager grid at +0x10.
unsigned char BfmeTaintManager::rva006C0840(int cellX, int cellY)
{
	return m_bfmeGrid->rva006C0E70(cellX, cellY);
}

// ?rva006C07F0@BfmeTaintManager@@QAEXXZ @ 0x006C07F0 8B
// Honest address name: tail-jmp thunk loading grid at +0x10 then jumping to
// pinned Gen_008812D0::bfmeReset (0x0069E440). Evidence: mov ecx,[ecx+0x10]
// plus jmp shape, BfmeTaintManager primary vtable 0x00CE7B84 slot 10.
void BfmeTaintManager::rva006C07F0()
{
	((Gen_008812D0 *)m_bfmeGrid)->bfmeReset();
}

struct BfmeFlagPair
{
	bool m_bfmeFirst;
	bool m_bfmeSecond;
};

class BfmeFlagTarget
{
public:
	virtual ~BfmeFlagTarget();
	virtual void pad1();
	virtual void pad2();
	virtual void pad3();
	virtual void pad4();
	virtual void pad5();
	virtual void pad6();
	virtual void pad7();
	virtual void pad8();
	virtual void pad9();
	virtual void bfmeDescribe(BfmeFlagPair *flags);
};

// The sink is the grid: its transfer 0x006C0F50 (rowed in
// BfmeGridRasterCircle.cpp) takes the target as its Xfer view.

class Gen_006C0A20
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	TaintManagerImpl *m_bfmeSink;
};

void Gen_006C0A20::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->rva006C0F50((GridXferView *)target);
}

