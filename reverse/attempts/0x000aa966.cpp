// ??0W3DAptDisplayString@@QAE@PAURva000AAD88Arg@@@Z
// partial score=0.98 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
// ??0W3DAptDisplayString@@QAE@PAURva000AAD88Arg@@@Z retail 0x000AA966
// 837 bytes. The W3DAptDisplayString constructor: w3dAllocateString
// (0x000AAD88; WorldBuilder 0x008A67E0 in W3DAptAux.cpp) news 0x30 bytes and
// returns this body's result; the WorldBuilder twin 0x008AAB50 (same file)
// stores the base then the derived vptr, and retail keeps the derived vptr
// 0x00BC9400 with EH state 0 for the base and 1 for the +0x04 name string.
// Members: +0x08 display string from TheDisplayStringManager slot 14; the
// +0x0C/+0x14 rectangle from the params' +0x04..+0x10 (scaled by the global
// x/y factors when the +0x2C flag copied from the global byte is set, the
// font size +0x48 by their minimum); +0x1C size (1 1); +0x24/+0x28 from the
// params' +0x2C/+0x14; +0x2D drop-shadow flag; +0x2E (no +0x28 or no
// +0x24). The font comes from FontLibrary::getFont; the "&dropShadow" suffix
// is cut from the params' +0x54 text; "$label" text is fetched from
// TheGameText (label kept as is with a ':' else "APT:%s"), other text goes
// through MultiByteToWideCharSingleLine; +0x24 sets the word wrap; an empty
// name calls SetText (0x000AA7B2) else the Apt window manager adds the
// display string; then the rowed 0x000A97A9 update runs on the params.

#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
#include <string.h>

typedef bool Bool;
typedef float Real;
typedef int Int;

extern "C" void __cdecl free(void *block);

class GameFont;
class Rva00222CCB;

namespace _STL {
template <class T> class char_traits;
template <class T> class allocator;
template <class C, class Tr, class A> class basic_string
{
public:
	~basic_string()
	{
		if (_M_start)
			free(_M_start);
	}
	const C *c_str() const { return _M_start; }
	C *_M_start;
	C *_M_finish;
	C *_M_end_of_storage;
};
}

typedef _STL::basic_string<unsigned short, _STL::char_traits<unsigned short>, _STL::allocator<unsigned short> > WideSTLString;

WideSTLString MultiByteToWideCharSingleLine(const char *orig);

class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, Real pointSize, Bool bold);
};
extern FontLibrary *TheFontLibrary;

class DisplayString
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void setFont(GameFont *font);			// +0x18
	virtual void slot07();
	virtual void setWordWrap(Int wordWrap);			// +0x20
	virtual void setWordWrapCentered(Bool isCentered);	// +0x24
};

class DisplayStringManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual DisplayString *newDisplayString();		// +0x38
};
extern DisplayStringManager *TheDisplayStringManager;

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists);	// +0x38
};
extern GameTextInterface *TheGameText;

class BfmeAptWindowManager
{
public:
	void rva00225299(const AsciiString &name, const UnicodeString &text, Rva00222CCB *displayString);
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva000A97A9
{
public:
	void rva000A97A9(void *dst);
};

// The Apt text-field parameters (w3dAllocateString's argument).
struct Rva000AAD88Arg
{
	const char *m_fontName;		// +0x00
	Real m_left;			// +0x04
	Real m_top;			// +0x08
	Real m_right;			// +0x0C
	Real m_bottom;			// +0x10
	Int m_14;			// +0x14
	char m_pad18[0x24 - 0x18];
	Int m_24;			// +0x24
	Int m_28;			// +0x28
	Int m_2c;			// +0x2C
	char m_pad30[0x48 - 0x30];
	Real m_fontSize;		// +0x48
	char m_pad4C[0x54 - 0x4C];
	const char *m_text;		// +0x54
};

// The Apt resolution scaling block inside g_00DB4CE0: the enable byte at
// 0x00DB4CE8 and the x/y factors at 0x00DB4CF0/0x00DB4CF4.
extern unsigned char g_00DB4CE0;
#define s_aptScaleEnabled (*(const Bool *)(&g_00DB4CE0 + 8))
#define s_aptScaleX (*(const Real *)(&g_00DB4CE0 + 0x10))
#define s_aptScaleY (*(const Real *)(&g_00DB4CE0 + 0x14))

static __forceinline char rawCharAt(const AsciiString &s, Int index)
{
	const char *text = *(const char *const *)&s;
	return text ? text[8 + index] : 0;
}

static __forceinline void setCoord(Coord2D &c, Real x, Real y)
{
	c.x = x;
	c.y = y;
}

class AptDisplayStringBase
{
public:
	AptDisplayStringBase() {}
	virtual ~AptDisplayStringBase();
};

class W3DAptDisplayString : public AptDisplayStringBase
{
public:
	W3DAptDisplayString(Rva000AAD88Arg *params);
	virtual ~W3DAptDisplayString();
	virtual void SetText(const UnicodeString &text);

private:
	AsciiString m_name;			// +0x04
	DisplayString *m_displayString;		// +0x08
	Coord2D m_topLeft;			// +0x0C
	Coord2D m_bottomRight;			// +0x14
	Coord2D m_size;				// +0x1C
	Int m_24;				// +0x24
	Int m_28;				// +0x28
	Bool m_scaled;				// +0x2C
	Bool m_dropShadow;			// +0x2D
	Bool m_2e;				// +0x2E
};

// ??0W3DAptDisplayString@@QAE@PAURva000AAD88Arg@@@Z @ 0x000AA966
W3DAptDisplayString::W3DAptDisplayString(Rva000AAD88Arg *params)
{
	m_displayString = 0;
	setCoord(m_topLeft, 0.0f, 0.0f);
	setCoord(m_bottomRight, 0.0f, 0.0f);
	setCoord(m_size, 1.0f, 1.0f);
	m_24 = params->m_2c;
	m_28 = params->m_14;
	m_scaled = s_aptScaleEnabled;
	m_dropShadow = false;
	m_2e = (params->m_28 == 0 || params->m_24 == 0);

	m_displayString = TheDisplayStringManager->newDisplayString();
	Real fontSize = params->m_fontSize;
	Real left = params->m_left;
	Real top = params->m_top;
	Real right = params->m_right;
	Real bottom = params->m_bottom;
	if (m_scaled)
	{
		Real scale = s_aptScaleX < s_aptScaleY ? s_aptScaleX : s_aptScaleY;
		fontSize *= scale;
		left *= s_aptScaleX;
		top *= s_aptScaleY;
		right *= s_aptScaleX;
		bottom *= s_aptScaleY;
	}
	m_topLeft.x = left;
	m_topLeft.y = top;
	m_bottomRight.x = right;
	m_bottomRight.y = bottom;

	GameFont *font;
	{
		AsciiString fontName(params->m_fontName);
		font = TheFontLibrary->getFont(&fontName, fontSize, false);
	}
	m_displayString->setFont(font);

	AsciiString text(params->m_text);
	for (Int i = 0; i < text.getLength(); i++)
	{
		if (rawCharAt(text, i) == '&' && _strcmpi(text.str() + i + 1, "dropShadow") == 0)
		{
			text = AsciiString(text.str(), i);
			m_dropShadow = true;
			break;
		}
	}

	UnicodeString utext;
	if (rawCharAt(text, 0) == '$')
	{
		const char *label = text.str() + 1;
		if (strchr(label, ':'))
			m_name = label;
		else
			m_name.format("APT:%s", label);
		Bool exists;
		utext = TheGameText->fetch(m_name, &exists);
	}
	else
	{
		utext = MultiByteToWideCharSingleLine(text.str()).c_str();
	}

	if (params->m_24)
	{
		m_displayString->setWordWrapCentered(m_28 == 2);
		m_displayString->setWordWrap((Int)(right - left));
	}

	if (((const StringBase<char> *)&m_name)->isEmpty())
		SetText(utext);
	else
		g_bfmeAptWindowManager->rva00225299(m_name, utext, (Rva00222CCB *)this);
	((Rva000A97A9 *)this)->rva000A97A9(params);
}
