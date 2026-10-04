// ?rva00496DA3@Rva00496DA3@@QAEPAXPAXABVAsciiString@@@Z
// partial score=0.96 date=2026-10-04
// ?rva00496DA3@Rva00496DA3@@QAEPAXPAXABVAsciiString@@@Z
// partial score=0.96 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs-c- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// ?rva00496DA3@Rva00496DA3@@QAEPAXPAXABVAsciiString@@@Z @ 0x00496DA3 98B: leaf vector at +0x18/0x1c of Elem* compareNoCase vs key on hit copy string at +0x54 else empty. Evidence: callees compareNoCase 0x00006A00 StringBase PBD 0x00037BA0 StringBase copy 0x000365F0 empty g_Rva0107301CEmptyString; caller 0x00496ED5; same shape as Rva00496D43 0x00496D43.
#include "ascii_string.h"
#include <new>

extern const char g_Rva0107301CEmptyString[];

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct Rva00496DA3Elem
{
	AsciiString m_key00;
	char m_pad04[0x50];
	AsciiString m_val54;
};

class Rva00496DA3
{
public:
	void *rva00496DA3(void *out, const AsciiString &key);
private:
	char m_pad00[0x18];
	Rva00496DA3Elem **m_begin18;
	Rva00496DA3Elem **m_end1C;
};

void *Rva00496DA3::rva00496DA3(void *out, const AsciiString &key)
{
	volatile unsigned i = 0;
	while (i < (unsigned)(m_end1C - m_begin18)) {
		_ReadWriteBarrier();
		if (m_begin18[i]->m_key00.compareNoCase(key) == 0) {
			__assume(out != 0);
			new (out) AsciiString(m_begin18[i]->m_val54);
			return out;
		}
		++i;
	}
	__assume(out != 0);
	new (out) AsciiString(g_Rva0107301CEmptyString);
	return out;
}