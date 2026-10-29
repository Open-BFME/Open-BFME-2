// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD
// platformsdk
//
// ?dumpThingTemplates@@YAXXZ retail 0x0021A1E1 (470B): a debugger-output
// listing of TheThingFactory's templates (first at +0x0C, next at +0x484) by
// class: five passes over the list, one per KindOf bit (+0x109 bit 0, +0x113
// bit 2, +0x109 bits 2, 1 and 3, labelled INFANTRY, HERO, MONSTER, CAVALRY
// and MACHINE), each matching template giving one OutputDebugStringA line of
// " <LABEL>\t SIDE: <side>\t<name>\n" from the +0x6C side and +0x64 name
// strings. The function and the template view keep address-derived names.
#include <windows.h>
#include "ascii_string.h"

class Rva0021A1E1Template
{
public:
	unsigned char m_pad000[0x64];
	AsciiString m_name; // +0x64
	unsigned char m_pad068[0x6C - 0x68];
	AsciiString m_side; // +0x6C
	unsigned char m_pad070[0x109 - 0x70];
	unsigned char m_kindOf109; // +0x109
	unsigned char m_pad10A[0x113 - 0x10A];
	unsigned char m_kindOf113; // +0x113
	unsigned char m_pad114[0x484 - 0x114];
	Rva0021A1E1Template *m_next; // +0x484
};

class ThingFactory;
extern ThingFactory *TheThingFactory;

struct Rva0021A1E1Factory
{
	unsigned char m_pad00[0x0C];
	Rva0021A1E1Template *m_first; // +0x0C
};

static __forceinline void rva0021A1E1Line(const char *label, const Rva0021A1E1Template *t)
{
	OutputDebugStringA(label);
	OutputDebugStringA(" SIDE: ");
	OutputDebugStringA(t->m_side.str());
	OutputDebugStringA("\t");
	OutputDebugStringA(t->m_name.str());
	OutputDebugStringA("\n");
}

void dumpThingTemplates()
{
	Rva0021A1E1Template *t;
	for (t = ((Rva0021A1E1Factory *)TheThingFactory)->m_first; t; t = t->m_next)
		if (t->m_kindOf109 & 1)
			rva0021A1E1Line(" INFANTRY\t", t);
	for (t = ((Rva0021A1E1Factory *)TheThingFactory)->m_first; t; t = t->m_next)
		if (t->m_kindOf113 & 4)
			rva0021A1E1Line(" HERO    \t", t);
	for (t = ((Rva0021A1E1Factory *)TheThingFactory)->m_first; t; t = t->m_next)
		if (t->m_kindOf109 & 4)
			rva0021A1E1Line(" MONSTER \t", t);
	for (t = ((Rva0021A1E1Factory *)TheThingFactory)->m_first; t; t = t->m_next)
		if (t->m_kindOf109 & 2)
			rva0021A1E1Line(" CAVALRY \t", t);
	for (t = ((Rva0021A1E1Factory *)TheThingFactory)->m_first; t; t = t->m_next)
		if (t->m_kindOf109 & 8)
			rva0021A1E1Line(" MACHINE \t", t);
}
