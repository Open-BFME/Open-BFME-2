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
	// declared here so the range updater below resolves it.
	void bfmeUpdate(int amount, bool absolute, int mode);
};

typedef void (__cdecl *BfmeCellVisitorFC)(int x, int y,
	unsigned char kind);

class Gen_008812D0
{
public:
	Gen_008812D0();
	void bfmeConfigure(Region3D region, Real cellSize);
	void bfmeGetCellRange(BfmeCellFC **first, BfmeCellFC **last,
		int x1, int x2, int y);

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

// ??1BfmeCellFC@@QAE@XZ present-unmatched
BfmeCellFC::~BfmeCellFC()
{
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
