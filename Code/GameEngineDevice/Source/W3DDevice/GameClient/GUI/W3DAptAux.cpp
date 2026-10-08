// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// W3DAptAux.cpp -- W3DAptAux members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function and
// asserts s_renderer ("Umm, no renderer"); retail compiles out the debug
// timers and statistics and keeps a NULL-renderer guard. Retail supplies the
// bytes.
//
// Target evidence: the renderer pointer at 0x00DE6170 is flushed through a
// thiscall at 0x001116E2 (unrowed, a jump to 0x00111319), then the 2D render
// state reset 0x00118990 runs, a counter (0x00DB5FB0) and a float
// (0x00DEC49C) are cleared and WW3D::Sync is called with the two sync times
// stored after the renderer (0x00DE6174, 0x00DE6178). Their names are
// unknown and keep address tokens.
#include "ascii_string.h"
#include "unicode_string.h"
#include <ctype.h>
#include <stdio.h>

typedef bool Bool;
typedef float Real;

typedef unsigned int UnsignedInt;
typedef int Int;

class WW3D
{
public:
	static void Sync(UnsignedInt sync_time);	// 0x00117490
};

void Rva00118990();					// 0x00118990

// The renderer behind s_renderer, placeholder-named by its bracketing calls.
class BfmeHub982
{
public:
	void rva001116E2();				// 0x001116E2
	void bfmeBegin982C();				// 0x00111319
	void bfmeEnd982C();				// 0x00110611
};

extern int g_Va00DB5FB0;
extern float g_Va00DEC49C;

class W3DAptAux
{
	friend void w3dCustomControlRender(const char *name, Int arg1, class AptRenderingUnit *renderingUnit, Int arg3);

public:
	static void PostDraw();

private:
	static BfmeHub982 *s_renderer;			// 0x00DE6170
	static UnsignedInt s_syncTime0;			// 0x00DE6174
	static UnsignedInt s_syncTime1;			// 0x00DE6178
};

// W3DAptAux::PostDraw, retail 0x000A9071.
void W3DAptAux::PostDraw()
{
	if (s_renderer)
	{
		s_renderer->rva001116E2();
		Rva00118990();
		g_Va00DB5FB0 = 0;
		g_Va00DEC49C = 0.0f;
		WW3D::Sync(s_syncTime0);
		WW3D::Sync(s_syncTime1);
	}
}

// getNameAndIndex, retail 0x000AA73A. Splits "...\\name123.ext" into the
// trailing frame index (parsed with "%d.") and either the full path or the
// file name after the last backslash. WB asserts both separators exist;
// retail returns NULL instead.
const char *getNameAndIndex(const AsciiString &path, Int *index, Bool fullPath)
{
	const char *fname = path.reverseFind('\\');
	if (!fname)
		return NULL;
	const char *digits = path.reverseFind('.');
	if (!digits)
		return NULL;
	while (isdigit(digits[-1]))
		--digits;
	sscanf(digits, "%d.", index);
	if (fullPath)
		return path.str();
	return fname + 1;
}

// Retail sets up no unwind frame around the getText() temporary, so the
// compare it calls cannot throw.
template <> int StringBase<unsigned short>::compare(const StringBase<unsigned short> &str) const throw();

// The game-client DisplayString as W3DAptDisplayString reaches it (virtual
// slots by offset; target evidence).
class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);		// +0x04
	virtual UnicodeString getText();			// +0x08
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void getSize(Int *width, Int *height);		// +0x3C
	virtual void slot40(); virtual void slot44();
	virtual void slot48(Real x, Real y);			// +0x48, called with (0, 0)
};

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

class W3DAptDisplayString
{
public:
	virtual void SetText(const UnicodeString &text);

private:
	unsigned char m_pad04[4];
	DisplayString *m_displayString;			// +0x08 (WB member name)
	unsigned char m_pad0C[0x1c - 0xc];
	Coord2D m_size;						// +0x1C
};

// W3DAptDisplayString::SetText, retail 0x000AA7B2.
void W3DAptDisplayString::SetText(const UnicodeString &text)
{
	if (m_displayString->getText().compare(text) == 0)
		return;
	m_displayString->slot48(0.0f, 0.0f);
	m_displayString->setText(text);
	Int width, height;
	m_displayString->getSize(&width, &height);
	m_size.x = (Real)width;
	m_size.y = (Real)height;
}

// The Apt-side render transform copied into each shape container before it
// draws (six dwords at 0x00DE6148; target evidence).
struct AptRenderTransform
{
	int m_data[6];
};

extern AptRenderTransform g_Va00DE6148;

class AptShapeContainer
{
public:
	void getRenderRegion(Coord2D &topLeft, Coord2D &bottomRight);	// 0x000A99B8

	unsigned char m_pad00[0x10];
	AptRenderTransform m_transform;				// +0x10
};

class AptRenderingUnit
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual AptShapeContainer *getShapes();			// +0x08
};

void rebuildMask();						// 0x000AA5E1
void Rva000A90B0(int);						// 0x000A90B0

// The Apt draw callback slot (0x00DB5FC8) and the Apt player (0x00DFE4CC),
// whose OnCustomRender (WB name) is rowed under a placeholder.
extern int g_Va00DB5FC8;

class Rva00223D8D
{
public:
	void rva00223D8D(const char *name, int topLeft, int bottomRight, int arg1, int arg3);	// 0x00223D8D
};

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

static inline Real roundToPixel(Real value)
{
	return (Real)(Int)(value + 0.5f);
}

// w3dCustomControlRender, retail 0x000AA645.
void w3dCustomControlRender(const char *name, Int arg1, AptRenderingUnit *renderingUnit, Int arg3)
{
	if (!renderingUnit)
		return;
	AptShapeContainer *shapes = renderingUnit->getShapes();
	if (!shapes)
		return;
	rebuildMask();
	int savedCallback = g_Va00DB5FC8;
	g_Va00DB5FC8 = (int)&Rva000A90B0;
	W3DAptAux::s_renderer->bfmeBegin982C();
	shapes->m_transform = g_Va00DE6148;
	Coord2D topLeft, bottomRight;
	shapes->getRenderRegion(topLeft, bottomRight);
	topLeft.x = roundToPixel(topLeft.x);
	topLeft.y = roundToPixel(topLeft.y);
	bottomRight.x = roundToPixel(bottomRight.x);
	bottomRight.y = roundToPixel(bottomRight.y);
	((Rva00223D8D *)g_bfmeAptWindowManager)->rva00223D8D(name, (int)&topLeft, (int)&bottomRight, arg1, arg3);
	g_Va00DB5FC8 = savedCallback;
	W3DAptAux::s_renderer->bfmeEnd982C();
}
