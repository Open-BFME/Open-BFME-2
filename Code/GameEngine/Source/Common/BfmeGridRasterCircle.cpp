// cl: /GX
// Distinct TU for two Bfme5SeventySix bodies (dest TU is twin-owned):
// ?bfmeRasterCircleFC@@YAXHHHVBfmeRangeUpdaterFC@@@Z @ 0x006C1150 (137B,
// b1 0x00881770) and ??0Gen_008812D0@@QAE@XZ @ 0x006C1490 (102B,
// b1 0x00881AA0). Trimmed copy of the BFME1 donor; bfmeConfigure and the
// range-updater call resolve through ledger pins.

// MSVC 7.1 folds `delete []` onto the scalar ??3@YAXPAX@Z unless the array
// form is declared where it can see it; retail calls ??_V@YAXPAX@Z here.
void operator delete[]( void *block );

typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);
void *__cdecl operator new[](unsigned int size);

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region3D
{
	__forceinline Region3D() {}

	__forceinline Region3D(const Region3D &other)
	{
		lo.x = other.lo.x;
		lo.y = other.lo.y;
		lo.z = other.lo.z;
		hi.x = other.hi.x;
		hi.y = other.hi.y;
		hi.z = other.hi.z;
	}

	__forceinline ~Region3D() {}

	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }

	Coord3D lo;
	Coord3D hi;
};

class BfmeCellFC
{
public:
	BfmeCellFC();
	~BfmeCellFC();

	unsigned char m_bfmeKind;				// +0x00
	unsigned char m_bfmeGap[3];				// +0x01
	int m_bfmeValue;					// +0x04
	int m_bfmeExtra;					// +0x08

	// BFME2 paints through a three-argument helper (retail 0x006C15E0);
	// defined below, kept out of line because retail calls it.
	__declspec(noinline) void bfmeUpdate(int amount, bool absolute, int mode);
};

typedef void (__cdecl *BfmeCellVisitorFC)(int x, int y,
	unsigned char kind);

struct BfmePointFC
{
	Real x;
	Real y;
};

class Gen_008812D0
{
public:
	Gen_008812D0();
	void bfmeConfigure(Region3D region, Real cellSize);
	void bfmeGetCellRange(BfmeCellFC **first, BfmeCellFC **last,
		int x1, int x2, int y);
	void bfmeApplyCircle(int x, int y, int radius, int amount, bool absolute, int mode);
	BfmeCellFC *bfmeCellAtWorld(Real worldX, Real worldY) const;
	int rva006C0E40(const BfmePointFC *point, int *extra);
	int rva006C0E70(int x, int y);
	int rva006C0EB0(const BfmePointFC *point) const;
	int rva006C0860(Real worldX) const;
	int rva006C0890(Real worldY) const;
	int rva006C08C0(Real distance) const;

	friend class BfmeRangeUpdaterFC;

private:
	Region3D m_bfmeRegion;					// +0x00
	Real m_bfmeCellSize;					// +0x18
	float m_bfmeCellSizeInv;				// +0x1C
	int m_bfmeWidth;					// +0x20
	int m_bfmeHeight;					// +0x24
	BfmeCellFC *m_bfmeCells;				// +0x28
	BfmeCellVisitorFC m_bfmeVisitor;			// +0x2C
};

class BfmeRangeUpdaterFC
{
public:
	__declspec(noinline) void operator()(int firstX, int lastX, int y);

	friend class Gen_008812D0;

private:
	// BFME2 carries a fourth paint-mode word after the amount; the flag stays
	// byte-sized at +0x0C (retail passes it through cl).
	Gen_008812D0 *m_bfmeGrid;				// +0x00
	int m_bfmeAmount;					// +0x04
	int m_bfmeMode;						// +0x08
	bool m_bfmeAbsolute;					// +0x0C
};

// ??0Gen_008812D0@@QAE@XZ
Gen_008812D0::Gen_008812D0()
{
	m_bfmeRegion.lo.zero();
	m_bfmeWidth = 0;
	m_bfmeHeight = 0;
	m_bfmeCells = 0;
	m_bfmeVisitor = 0;
	m_bfmeCellSize = 1.0f;
	m_bfmeRegion.hi.zero();

	bfmeConfigure(m_bfmeRegion, 1.0f);
}

// ?bfmeRasterCircleFC@@YAXHHHVBfmeRangeUpdaterFC@@@Z
void __cdecl bfmeRasterCircleFC(int centerX, int centerY, const int radius,
	BfmeRangeUpdaterFC updater)
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

			updater(firstX, lastX, centerY + y);
			if (y == 0)
				return;

			updater(firstX, lastX, centerY - y);
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

// ??RBfmeRangeUpdaterFC@@QAEXHHH@Z
void BfmeRangeUpdaterFC::operator()(int firstX, int lastX, int y)
{
	BfmeCellFC *first;
	BfmeCellFC *last;
	m_bfmeGrid->bfmeGetCellRange(&first, &last, firstX, lastX, y);

	for (BfmeCellFC *cell = first; cell != last; ++cell)
	{
		cell->bfmeUpdate(m_bfmeAmount, m_bfmeAbsolute, m_bfmeMode);
		m_bfmeGrid->m_bfmeVisitor(firstX, y, cell->m_bfmeKind);
		++firstX;
	}
}

// ?bfmeGetCellRange@Gen_008812D0@@QAEXPAPAVBfmeCellFC@@0HHH@Z
void Gen_008812D0::bfmeGetCellRange(BfmeCellFC **first,
	BfmeCellFC **last, int x1, int x2, int y)
{
	if (x2 < 0 || x1 >= m_bfmeWidth || y < 0 || y >= m_bfmeHeight)
	{
		*last = 0;
		*first = 0;
		return;
	}

	BfmeCellFC *row = m_bfmeCells + y * m_bfmeWidth;
	*last = row;
	*first = row;
	if (x1 > 0)
		*first = row + x1;

	*last += x2 < m_bfmeWidth ? x2 + 1 : m_bfmeWidth;
}


// BFME 2's cell grows a third field that its constructor (0x006C0BA0) sets to
// -1; new[] passes that constructor and the empty destructor to the array
// helper, so both are defined here rather than left implicit.
BfmeCellFC::BfmeCellFC()
	: m_bfmeKind(0x80), m_bfmeValue(0), m_bfmeExtra(-1)
{
}

// ?bfmeUpdate@BfmeCellFC@@QAEXH_NH@Z @ 0x006C15E0 101B
// The three-argument paint the range updater calls (BFME 1 inlines a two-
// argument form). Target evidence: the updater's call site, ret 0xC, and the
// +0/+4/+8 cell fields the constructor above initialises. A neutral (0x80)
// paint only clears a cell its own mode owns; the kind is added unless the
// paint is absolute, clamped to a byte, and a non-neutral kind records which
// side of neutral it sits on (1 above, 2 below) and the painting mode.
void BfmeCellFC::bfmeUpdate(int amount, bool absolute, int mode)
{
	if (mode != -1 && amount == 0x80 && mode != m_bfmeExtra)
		return;

	if (!absolute)
		amount += m_bfmeKind;
	if (amount < 0)
		amount = 0;
	else if (amount > 0xFF)
		amount = 0xFF;

	m_bfmeKind = (unsigned char)amount;
	if (m_bfmeKind == 0x80)
	{
		mode = -1;
		m_bfmeValue = 0;
	}
	else
		m_bfmeValue = m_bfmeKind > 0x80 ? 1 : 2;
	m_bfmeExtra = mode;
}

// Transferred from BFME 1's taintmanager_impl.cpp; only the cell size differs.
// ?bfmeConfigure@Gen_008812D0@@QAEXURegion3D@@M@Z
void Gen_008812D0::bfmeConfigure(Region3D region, Real cellSize)
{
	if (region.width() < 1.0f)
		region.hi.x = region.lo.x + 1.0f;
	if (region.height() < 1.0f)
		region.hi.y = region.lo.y + 1.0f;

	Real cellSizeInv = 1.0f / cellSize;
	int width = bfmeFloatToLongFC(bfmeFloatCeilFC(
		region.width() * cellSizeInv));
	if (width < 1)
		width = 1;
	int height = bfmeFloatToLongFC(bfmeFloatCeilFC(
		region.height() * cellSizeInv));
	if (height < 1)
		height = 1;

	BfmeCellFC *cells = new BfmeCellFC[width * height];
	BfmeCellFC *cell = cells;
	for (unsigned int y = 0; y < (unsigned int)height; ++y)
	{
		int oldY = bfmeFloatToLongFC(bfmeFloatFloorFC(
			((Real)y * cellSize + region.lo.y - m_bfmeRegion.lo.y)
				* m_bfmeCellSizeInv));
		if (oldY >= 0 && oldY < m_bfmeHeight)
		{
			for (unsigned int x = 0; x < (unsigned int)width;
				++x, ++cell)
			{
				int oldX = bfmeFloatToLongFC(bfmeFloatFloorFC(
					((Real)x * cellSize + region.lo.x - m_bfmeRegion.lo.x)
						* m_bfmeCellSizeInv));
				if (oldX >= 0 && oldX < m_bfmeWidth)
					cell->m_bfmeKind = m_bfmeCells[
						oldY * m_bfmeWidth + oldX].m_bfmeKind;
			}
		}
		else
		{
			cell += width;
		}
	}

	delete[] m_bfmeCells;
	m_bfmeCells = cells;
	m_bfmeRegion = region;
	m_bfmeCellSizeInv = cellSizeInv;
	m_bfmeWidth = width;
	m_bfmeHeight = height;
	m_bfmeCellSize = cellSize;
}

// Retail 0x006C1580 86B: circle paint via bfmeRasterCircleFC; early-out on
// radius<0 and on (amount==0 && !absolute). BFME2 adds trailing mode word.
void Gen_008812D0::bfmeApplyCircle(int x, int y, int radius, int amount, bool absolute, int mode)
{
	if (radius < 0)
		return;
	if (amount == 0 && !absolute)
		return;
	BfmeRangeUpdaterFC updater;
	updater.m_bfmeGrid = this;
	updater.m_bfmeAmount = amount;
	updater.m_bfmeMode = mode;
	updater.m_bfmeAbsolute = absolute;
	bfmeRasterCircleFC(x, y, radius, updater);
}

// Retail 0x006C0BD0 135B: world-to-cell via floor/inv, null when outside.
// Evidence: same lo.x/lo.y at +0x00/+0x04 and inv at +0x1C as ApplyWorld,
// 12-byte cells via x3/x4 lea pair, unlock callers 0x006C0E40/0x006C0E70.
BfmeCellFC *Gen_008812D0::bfmeCellAtWorld(Real worldX, Real worldY) const
{
	int x = bfmeFloatToLongFC(bfmeFloatFloorFC((worldX - m_bfmeRegion.lo.x) * m_bfmeCellSizeInv));
	if (x < 0 || x >= m_bfmeWidth)
		return 0;
	int y = bfmeFloatToLongFC(bfmeFloatFloorFC((worldY - m_bfmeRegion.lo.y) * m_bfmeCellSizeInv));
	if (y < 0 || y >= m_bfmeHeight)
		return 0;
	return &m_bfmeCells[y * m_bfmeWidth + x];
}

// ?rva006C0E40@Gen_008812D0@@QAEHPBUBfmePointFC@@PAH@Z @ 0x006C0E40 40B
// Honest address name: thiscall forwards ECX to bfmeCellAtWorld, so the
// owner is Gen_008812D0. Takes world XY plus out-word; returns m_bfmeValue
// and stores m_bfmeExtra, 0 when outside. Evidence: ECX passthrough call to
// rowed bfmeCellAtWorld 0x006C0BD0, +8/+4 cell reads, ret 8, tail-jmp thunk
// at 0x006C0850 via +0x10 grid member.
int Gen_008812D0::rva006C0E40(const BfmePointFC *point, int *extra)
{
	BfmeCellFC *cell = bfmeCellAtWorld(point->x, point->y);
	if (cell != 0)
	{
		*extra = cell->m_bfmeExtra;
		return cell->m_bfmeValue;
	}
	return 0;
}

// ?rva006C0E70@Gen_008812D0@@QAEHHH@Z @ 0x006C0E70 63B
// Honest address name: thiscall reads width/height/cells at +0x20/+0x24/+0x28
// so owner is Gen_008812D0. Returns cell kind byte or 0x80 default when out
// of bounds. Evidence: gap between rowed 0x006C0E40 and range updater in same
// /GX TU, imul width*y plus x3 x4 lea for 12B cells, tail-jmp thunk at
// 0x006C0840 via grid member.
int Gen_008812D0::rva006C0E70(int x, int y)
{
	if (x < 0 || x >= m_bfmeWidth)
		return 0x80;
	if (y < 0 || y >= m_bfmeHeight)
		return 0x80;
	BfmeCellFC *cell = &m_bfmeCells[y * m_bfmeWidth + x];
	if (cell == 0)
		return 0x80;
	return cell->m_bfmeKind;
}

// ?rva006C0EB0@Gen_008812D0@@QBEHPBUBfmePointFC@@@Z @ 0x006C0EB0 34B
// Transferred from Open-BFME-1's taintmanager_impl.cpp (submodule 968ca36c:
// rva00881500, BFME 1 0x00881500), whose compiled body masks to exactly one
// hit in this image, free ground between rowed 0x006C0E70 and the range
// updater at 0x006C0EE0. The m_bfmeKind twin of rva006C0E40: the same
// thiscall to the rowed bfmeCellAtWorld, and 0x80 (BfmeCellFC's default
// kind) when the point is outside the grid. The name is this image's address.
int Gen_008812D0::rva006C0EB0(const BfmePointFC *point) const
{
	BfmeCellFC *cell = bfmeCellAtWorld(point->x, point->y);
	return cell ? cell->m_bfmeKind : 0x80;
}

// Three world-to-cell helpers from Open-BFME-1's taintmanager_impl.cpp
// (submodule 10af19f44a: rva00880E70 / rva00880EA0 / rva00880ED0, BFME 1
// 0x00880E70 / 0x00880EA0 / 0x00880ED0), byte-identical here at 0x006C0860,
// 0x006C0890 and 0x006C08C0, in the same order and 0x30 apart. BFME 1 folds
// each with other copies, so the names are this image's addresses.
// ?rva006C0860@Gen_008812D0@@QBEHM@Z: world x to cell column (floor).
int Gen_008812D0::rva006C0860(Real worldX) const
{
	return bfmeFloatToLongFC(bfmeFloatFloorFC(
		(worldX - m_bfmeRegion.lo.x) * m_bfmeCellSizeInv));
}

// ?rva006C0890@Gen_008812D0@@QBEHM@Z: world y to cell row (floor).
int Gen_008812D0::rva006C0890(Real worldY) const
{
	return bfmeFloatToLongFC(bfmeFloatFloorFC(
		(worldY - m_bfmeRegion.lo.y) * m_bfmeCellSizeInv));
}

// ?rva006C08C0@Gen_008812D0@@QBEHM@Z: a distance in cells (ceiling).
int Gen_008812D0::rva006C08C0(Real distance) const
{
	return bfmeFloatToLongFC(bfmeFloatCeilFC(distance * m_bfmeCellSizeInv));
}
