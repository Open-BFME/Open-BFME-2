// ??1Rva004EDCE9@@UAE@XZ
// cl: /Ireference/shims/bfme2_ascii /MD /EHs
// ??1Rva004EDCE9@@UAE@XZ at 0x004EDCE9 (100B).
// Base dtor with vtable 0x008629E4, stop call 0x004ED748(0 1),
// AsciiString at +0x2C via releaseBuffer, frees of +0x14 then +0x4.
// Evidence: retail vptr store + push 1 push 0 call 0x4ED748 with EH2,
// lea ecx [esi+0x2C] call releaseBuffer EH1, test/free +0x14 EH0,
// then free +0x4; tail-called by 4 derived dtors in Rva004EDCE9Derived.cpp;
// LINK BONUS 156B file waits for this name.
#include "ascii_string.h"

class AITactic
{
public:
	void end(bool a, bool b);
};

extern "C" void __cdecl free(void *p);

struct Rva004EDCE9Buf
{
	void *m_p;
	~Rva004EDCE9Buf()
	{
		if (m_p != 0)
			free(m_p);
	}
};

class Rva004EDCE9
{
public:
	virtual ~Rva004EDCE9();
private:
	Rva004EDCE9Buf m_04; // +4
	char m_pad08[0x14 - 0x08]; // +8
	Rva004EDCE9Buf m_14; // +0x14
	char m_pad18[0x2C - 0x18]; // +0x18
	AsciiString m_2C; // +0x2C
	char m_pad30[0x54 - 0x30]; // tail to cover +0x38/+0x50 uses in 0x004ED748
};

Rva004EDCE9::~Rva004EDCE9()
{
	((AITactic *)this)->end(0, 1);
}
