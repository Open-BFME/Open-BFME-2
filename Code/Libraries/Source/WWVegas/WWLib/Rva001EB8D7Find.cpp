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

// ?rva001EB8A4@Rva001EB8A4@@QAE_NABURva001EB8A4Elem@@@Z @0x001EB8A4 51B
// Evidence: unlock; vector StringBase at 0x18 0x1C stride 4 compareNoCase 0x6A00; arg StringBase at +4; caller 0x001EC795.
struct Rva001EB8A4Elem
{
	char m_pad00[4];
	StringBase<char> m_str04;
};

class Rva001EB8A4
{
public:
	bool rva001EB8A4(const Rva001EB8A4Elem &e);
private:
	char m_pad00[0x18];
	StringBase<char> *m_begin18;
	StringBase<char> *m_end1C;
	StringBase<char> *m_cap20;
};

bool Rva001EB8A4::rva001EB8A4(const Rva001EB8A4Elem &e)
{
	StringBase<char> *p = m_begin18;
	StringBase<char> *last = m_end1C;
	for (; p != last; ++p)
	{
		if (e.m_str04.compareNoCase(*p) == 0)
			return true;
	}
	return false;
}
