// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// ?rva001EB8D7@Rva001EB8D7@@QAEHABV?$StringBase@D@@@Z @0x001EB8D7 53B
// Evidence: linkbody; callee compareNoCase 0x00006A00; loop over 0x24 stride with idiv; callers 0x001EB913 and 0x00514D73; unblocks 0x001EB90C.
#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva001EB8D7
{
public:
	int rva001EB8D7(const StringBase<char> &s);
	void *rva001EB90C(const StringBase<char> &s);
private:
	struct Elem
	{
		StringBase<char> m_str;
		char m_pad[0x24 - 4];
	};
	char m_pad00[0x14];
	Elem *m_start14;
	Elem *m_finish18;
	Elem *m_end1C;
};

int Rva001EB8D7::rva001EB8D7(const StringBase<char> &s)
{
	Elem *p = m_start14;
	while (p != m_finish18)
	{
		if (p->m_str.compareNoCase(s) == 0)
			return (p - m_start14);
		++p;
	}
	return -1;
}

// ?rva001EB90C@Rva001EB8D7@@QAEPAXABV?$StringBase@D@@@Z @0x001EB90C 52B
// Evidence: chain from 0x001EB8D7; same this offsets 0x14 0x18 stride 0x24; caller 0x001EBC01.
void *Rva001EB8D7::rva001EB90C(const StringBase<char> &s)
{
	int idx = rva001EB8D7(s);
	unsigned num = (unsigned)(m_finish18 - m_start14);
	if (idx < 0 || (unsigned)idx >= num)
		return 0;
	_ReadWriteBarrier();
	return m_start14 + idx;
}
