// ?rva003B9EC4@@YAHPAURva003B9EC4Arg@@H@Z
// partial score=0.6 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?rva003B9EC4@@YAHPAURva003B9EC4Arg@@H@Z @0x003B9EC4 108B: with at least two arguments, copy
// the second argument into the global string at 0x00DFE7B0, set the flag bytes on the holder
// at 0x00DFE758 and return 2; otherwise return 1.
#include "ascii_string.h"

extern void *g_00DFE758;
extern StringBase<char> g_00DFE7B0;
extern unsigned char g_00DFE7A8;

struct Rva003B9EC4Arg
{
	char m_pad00[4];
	const char *m_04;
};

// ?rva003B9EC4@@YAHPAURva003B9EC4Arg@@H@Z @0x003B9EC4
int __cdecl rva003B9EC4(Rva003B9EC4Arg *arg, int argc)
{
	if (argc >= 2)
	{
		AsciiString text(arg->m_04);
		g_00DFE7B0.set(reinterpret_cast<const StringBase<char> &>(text));
		g_00DFE7A8 = 1;
		((unsigned char *)g_00DFE758)[0x2C] = 1;
		((unsigned char *)g_00DFE758)[0xAF0] = 0;
		return 2;
	}
	return 1;
}
