// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva005394F0@Rva005394F0@@QAEXHH@Z retail 0x005394F0..0x00539611
// (289 bytes ret 8). Reached only through the forwarder 0x00539611 (the
// +0x08 object of its host) which passes its two dwords on unchanged.
// Draws up to two text lines stacked downwards: each line is a Unicode
// string (+0x04 and +0x08; skipped when StringBase<unsigned short>::isEmpty
// 0x00035740 says so) with its display string (+0x0C and +0x10). The line is
// centred horizontally inside the width at the second argument (x = pos.x +
// (width - textWidth) * 0.5) and drawn through vtable +0x34 at the floored
// rounded position (msvcr71 floor then the fld/fistp REAL_TO_INT_FLOOR
// idiom) before y advances by the text height (size from vtable +0x3C).
// Both arguments are read as pointers to float pairs: the pinned spelling
// (int int) is kept so the forwarder keeps resolving and the pointers are
// recovered from those dwords. No donor or WorldBuilder twin; the class
// and field names are address-derived.
#include "string_base.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"

typedef float Real;
typedef int Int;

extern "C" __declspec(dllimport) double __cdecl floor(double);

// BaseType.h's inline fld/fistp rounding; retail floors through msvcr71.
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

__forceinline float fast_float_floor(float f)
{
	return (float)floor((double)f);
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

class Rva005394F0Text
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12();
	virtual void draw(Int x, Int y); // +0x34
	virtual void slot14();
	virtual void getSize(Int *width, Int *height); // +0x3C
};

class Rva005394F0
{
public:
	void rva005394F0(Int a0, Int a1);

private:
	void *m_00;
	StringBase<unsigned short> m_line1; // +0x04
	StringBase<unsigned short> m_line2; // +0x08
	Rva005394F0Text *m_text1; // +0x0C
	Rva005394F0Text *m_text2; // +0x10
};

void Rva005394F0::rva005394F0(Int a0, Int a1)
{
	const Coord2D *pos = reinterpret_cast<const Coord2D *>(a0);
	const Coord2D *size = reinterpret_cast<const Coord2D *>(a1);
	Real y = pos->y;

	if (!m_line1.isEmpty())
	{
		Int width, height;
		m_text1->getSize(&width, &height);
		Real x = pos->x + (size->x - width) * 0.5f;
		m_text1->draw(REAL_TO_INT_FLOOR(x + 0.5f), REAL_TO_INT_FLOOR(y + 0.5f));
		y += height;
	}

	if (!m_line2.isEmpty())
	{
		Int width, height;
		m_text2->getSize(&width, &height);
		Real x = pos->x + (size->x - width) * 0.5f;
		m_text2->draw(REAL_TO_INT_FLOOR(x + 0.5f), REAL_TO_INT_FLOOR(y + 0.5f));
	}
}
