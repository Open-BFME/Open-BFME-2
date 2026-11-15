#include "../../Include/Common/Rva0023C641Storage.h"
// rva003B9EC4
// Retail 0x003B9EC4, 108 B. Address-derived name: the caller set and the
// owner of the timing-log object are not proven, so no semantic
// identity is claimed. Sets the timing-log enable byte at 0x00DFE7A8.
// cl: /O1 /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

class GlobalData;
extern GlobalData *TheWritableGlobalData;
// VA 0x00DFE7A8: one 152-byte object, constructed and cleaned up by
// the existing rowed CRT paths. The string at +8 is a member, not a global.
Rva0023C641Storage g_00DFE7A8;

struct Rva003B9EC4Arg { char m_pad00[4]; const char *m_04; };

int __cdecl rva003B9EC4(Rva003B9EC4Arg *arg, int argc)
{
	if (argc >= 2)
	{
		{
			AsciiString text(arg->m_04);
			((StringBase<char> *)&g_00DFE7A8.m_name08)->set(reinterpret_cast<const StringBase<char> &>(text));
		}
		g_00DFE7A8.m_enabled = 1;
		((unsigned char *)TheWritableGlobalData)[0x2C] = 1;
		((unsigned char *)TheWritableGlobalData)[0xAF0] = 0;
		return 2;
	}
	return 1;
}
