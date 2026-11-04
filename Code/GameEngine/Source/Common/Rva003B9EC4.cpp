// rva003B9EC4
// Retail 0x003B9EC4, 108 B. Address-derived name: the caller set and the
// owner of the 144-byte global at 0x00DFE7B0 are not proven, so no semantic
// identity is claimed. Sets the timing-log enable byte at 0x00DFE7A8.
// cl: /O1 /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

class GlobalData;
extern GlobalData *TheWritableGlobalData;
// VA 0x00DFE7B0 (RVA 0x009DFE7B0): the 144-byte string base this body writes
// the timing-log key into. Retail's storage lies in .data's zero-filled tail
// (the section's raw data ends at RVA 0x009DE008), so the definition is
// zero-initialised, matching the empty string retail holds. The shim's
// StringBase default constructor is private (AsciiString alone is its
// friend), so the object is defined with the AsciiString spelling -- the
// one-pointer layout twin -- and reached through the no-op twin cast, the
// same idiom the other g_ string keys in this family use.
AsciiString g_00DFE7B0;
// VA 0x00DFE7A8 (RVA 0x009FE7A8): the timing-log enable byte this body sets.
// Retail's storage sits in .data's zero-filled tail (the section's raw data ends
// at RVA 0x009DE008, so the address loads as zero), so the definition that owns
// the symbol is zero-initialised, exactly as retail's image holds it.
// The first byte of a larger object: retail constructs it here with 0x0023DBF9, which writes out to +0x88, and
// the ledger's next object starts at +0x98. Its readers declare the byte under this name.
extern "C" { unsigned char __identifier("?g_00DFE7A8@@3EA")[0x98]; }

struct Rva003B9EC4Arg { char m_pad00[4]; const char *m_04; };

int __cdecl rva003B9EC4(Rva003B9EC4Arg *arg, int argc)
{
	if (argc >= 2)
	{
		{
			AsciiString text(arg->m_04);
			((StringBase<char> *)&g_00DFE7B0)->set(reinterpret_cast<const StringBase<char> &>(text));
		}
		__identifier("?g_00DFE7A8@@3EA")[0] = 1;
		((unsigned char *)TheWritableGlobalData)[0x2C] = 1;
		((unsigned char *)TheWritableGlobalData)[0xAF0] = 0;
		return 2;
	}
	return 1;
}
