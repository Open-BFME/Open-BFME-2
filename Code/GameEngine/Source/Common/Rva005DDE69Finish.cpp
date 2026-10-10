// cl: /MD
//
// ?rva005DDE69@Rva005DDE69@@QAEMIII@Z @0x005DDE69 54B. Bounds-checked wrapper
// over range-max 0x005DDCA5; count from byte range at +4/+8 divided by 0x18,
// returns 0x00BBB8DC float when index out of range, else delegates.
// Caller 0x005DE1B2. Honest address name. The read/write barrier keeps the
// compiler from caching m_begin across the idiv, which is the register shape
// retail uses; it emits no code.
// The range-max provider in GameStats.cpp uses the same pooled -FLT_MAX.
extern float g_Va00BBB8E0;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva005DDC6B
{
public:
	float rva005DDCA5(unsigned lo, unsigned hi);
	float rva005DDCE5(unsigned lo, unsigned hi);
};

class Rva005DDE69
{
public:
	float rva005DDE69(unsigned idx, unsigned lo, unsigned hi);
	float rva005DDE9F(unsigned idx, unsigned lo, unsigned hi);
private:
	char m_pad00[4];
	char *m_begin;
	char *m_end;
};

float Rva005DDE69::rva005DDE69(unsigned idx, unsigned lo, unsigned hi)
{
	int count = (m_end - m_begin) / 0x18;
	_ReadWriteBarrier();
	if (idx >= (unsigned)count)
		return -3.4028235e+38f;
	return ((Rva005DDC6B *)(m_begin + idx * 0x18))->rva005DDCA5(lo, hi);
}

// ?rva005DDE9F@Rva005DDE69@@QAEMIII@Z @0x005DDE9F 54B. Bounds-checked wrapper
// over range-min 0x005DDCE5; same stride as 0x005DDE69, returns 0x00BBB8E0
// float when out of range. Caller 0x005DE1E8 in 0x005DE100.
float Rva005DDE69::rva005DDE9F(unsigned idx, unsigned lo, unsigned hi)
{
	int count = (m_end - m_begin) / 0x18;
	_ReadWriteBarrier();
	if (idx >= (unsigned)count)
		return g_Va00BBB8E0;
	return ((Rva005DDC6B *)(m_begin + idx * 0x18))->rva005DDCE5(lo, hi);
}
