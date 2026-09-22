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
	unsigned char m_bfmeKind;				// +0x00
	unsigned char m_bfmeGap[3];				// +0x01
	int m_bfmeValue;					// +0x04
	int m_bfmeExtra;					// +0x08
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
	Gen_008812D0 *m_bfmeGrid;
	int m_bfmeAmount;
	bool m_bfmeAbsolute;
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
