// cl: /Ireference/shims/bfme2_ascii /O1 /MD
//
// 0x00142C80, the indexed lea this file was named for, is
// RenderInfoClass::Current_Override_Flags and lives in WW3D2/rinfo.cpp.
//
// ?rva0030812E@Rva0030812E@@QAEPAXH@Z, retail 0x0030812E, 11 bytes.
// Stack-indexed lea: mov eax [esp+4] lea eax [ecx+eax*4+0x78] ret 4.
// Spelled as byte arithmetic (no array size claimed); unlocks 0x7EDBC/
// 0x81E36/0x81CDF. Honest address name.
//
// ?rva003080AA@Rva003080AA@@QAEPAURva003080AARef@@H@Z, retail 0x003080AA, 25B.
// AddRef fetch from array at +0xB8:
// p=m_items[i]; if (p) ++p->m_ref; return m_items[i] (reload for return).
// Callers 0x38D9E/0x380C9. Honest address name.
//
// ?rva00308139@Rva00308139@@QAEXABVAsciiString@@@Z, retail 0x00308139, 29B.
// AsciiString assign to member+0x80 via pinned operator= then flag+0x88=1.
// Caller 0x392A9. Same flags.

#include "ascii_string.h"	// shared AsciiString: operator= expands to StringBase<char>::set (0x000366F0), as retail

struct Rva003080AARef
{
	virtual void _slot00();
	int m_ref04;
};

class Rva003080AA
{
	char m_pad00[0xb8];
	Rva003080AARef *m_itemsB8[32];

public:
	Rva003080AARef *rva003080AA(int i);
};

class Rva0030812E
{
public:
	void *rva0030812E(int i);
};

void *Rva0030812E::rva0030812E(int i)
{
	return (char *)this + 0x78 + i * 4;
}

Rva003080AARef *Rva003080AA::rva003080AA(int i)
{
	Rva003080AARef *p = m_itemsB8[i];
	if (p)
		p->m_ref04++;
	return m_itemsB8[i];
}

class Rva00308139
{
public:
	void rva00308139(const AsciiString &s);
private:
	char m_pad00[0x80];
	AsciiString m_str80;
	char m_pad84[4];
	bool m_flag88;
};

void Rva00308139::rva00308139(const AsciiString &s)
{
	m_str80 = s;
	m_flag88 = true;
}

//
// ?rva0030815D@Rva0030815D@@QAEXABVAsciiString@@@Z, retail 0x0030815D, 29B.
// AsciiString assign to member+0x8c via pinned operator= then flag+0x9c=1.
// Caller 0x3092CC in 0x3091B1. Same recipe/flags as 0x00308139. Honest address name.

class Rva0030815D
{
public:
	void rva0030815D(const AsciiString &s);
private:
	char m_pad00[0x8c];
	AsciiString m_str8C;
	char m_pad90[0x9c - 0x90];
	bool m_flag9C;
};

void Rva0030815D::rva0030815D(const AsciiString &s)
{
	m_str8C = s;
	m_flag9C = true;
}
