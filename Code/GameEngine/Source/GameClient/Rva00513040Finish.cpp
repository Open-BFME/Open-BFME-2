// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ?rva00513040@Rva00513040@@QAEXHH@Z @0x00513040 162B. __thiscall UI firer:
// formats two ints with "%d" into AsciiString locals, then invokes
// "SetBarPercent" with (owner +0x274, 2, str1, str2, 0, 0, 0) through the
// pinned Rva00222A8B target. Evidence: callers 0x004D45BA and 0x0051352B;
// rowed AsciiString::format 0x00038150 and StringBase releaseBuffer 0x00036410.
//
// Exact under /O1 once the second string's empty-or-data selection is
// evaluated before the first (p2 then p1); the banked 0.99 attempt declared the
// private AsciiString copy and selected p1 first, diverging at +0x3F.
#include "ascii_string.h"

class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

class Rva00513040
{
public:
	void rva00513040(int v1, int v2);

private:
	char m_pad[0x274];
	void *m_owner;
};

void Rva00513040::rva00513040(int v1, int v2)
{
	AsciiString s1;
	s1.format("%d", v1);
	AsciiString s2;
	s2.format("%d", v2);
	const char *p2 = s2.str();
	const char *p1 = s1.str();
	void *owner = m_owner;
	TheRva00222A8BTarget->invoke(owner, "SetBarPercent", 2, p1, (void *)p2, 0, 0, 0);
}
