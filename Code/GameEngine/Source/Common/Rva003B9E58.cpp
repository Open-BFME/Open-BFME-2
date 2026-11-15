#include "../../Include/Common/Rva0023C641Storage.h"
// rva003B9E58
// Retail 0x003B9E58, 108 B (EH, cdecl), an EH-prolog start Ghidra never
// listed; the twin of the rowed Rva003B9EC4.cpp command-line option handler
// that follows it. With an operand it stores the next argument into the
// string base at 0x00DFE7AC, sets the byte at 0x00DFE7A8 and the two
// TheWritableGlobalData bytes (+0x2C set, +0xAF0 cleared) and consumes two
// arguments; without one it consumes one. The option's name and the
// string's owner are not proven (address names).
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

class GlobalData;
extern GlobalData *TheWritableGlobalData;
// The enable byte the sibling owns (Rva003B9EC4.cpp).

struct Rva003B9E58Arg { char m_pad00[4]; const char *m_04; };

int __cdecl rva003B9E58(Rva003B9E58Arg *arg, int argc)
{
	if (argc >= 2)
	{
		{
			AsciiString text(arg->m_04);
			((StringBase<char> *)&g_00DFE7A8.m_name04)->set(reinterpret_cast<const StringBase<char> &>(text));
		}
		g_00DFE7A8.m_enabled = 1;
		((unsigned char *)TheWritableGlobalData)[0x2C] = 1;
		((unsigned char *)TheWritableGlobalData)[0xAF0] = 0;
		return 2;
	}
	return 1;
}
