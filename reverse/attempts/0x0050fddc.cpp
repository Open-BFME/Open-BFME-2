// ??1Rva0050FDDC@@UAE@XZ
// partial score=0.95 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ??1Rva0050FDDC@@UAE@XZ retail 0x0050FDDC 248B
// Derived dtor: formats "_level%u.%s" from m_5c/m_60 then closes _InitTextEntry
// and _InitSlider Apt screens via pin-only _bfme_closeAptScreen, destroys tmp
// and m_60 via rowed releaseBuffer, then base dtor pinned 0x005248D0.
// Evidence: vtable stores 0x008655BC/0x00865518, format 0x00038150,
// operator+ 0x000B49C5 plus conversion 0x000BC4F7, close pin 0x0041149A,
// releaseBuffer 0x00036410, empty fallback 0x007BAC1C, caller deleting dtor 0x0051062D.
#include "ascii_string.h"

extern const char g_Rva0107301CEmptyString[];

__forceinline const char *GetStr0050FDDC(const AsciiString &s)
{
	char *t = *(char * *)(const void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

class Rva000B3F84Pair
{
public:
	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusText : AsciiStringRef
{
	operator AsciiString();
	Rva000B3F84Pair m_right;
};

struct AsciiStringPlusText __cdecl operator+(const AsciiString &lhs, const char *rhs);

void _bfme_closeAptScreen(const AsciiString &name);

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	char m_pad04[0x5c - 4];
};

class Rva0050FDDC : public Rva005248D0
{
public:
	virtual ~Rva0050FDDC();
private:
	unsigned int m_5c;
	AsciiString m_60;
};

// ??1Rva0050FDDC@@UAE@XZ present-unmatched
Rva0050FDDC::~Rva0050FDDC()
{
	AsciiString tmp;
	tmp.format("_level%u.%s", m_5c, GetStr0050FDDC(m_60));
	_bfme_closeAptScreen(tmp + "_InitTextEntry");
	_bfme_closeAptScreen(tmp + "_InitSlider");
}
