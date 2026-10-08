// cl: /MD /EHsc /D_CRTIMP= /Ireference/shims/bfme2_ascii
// ??1Rva005DB221@@UAE@XZ @0x005DB221 80B
// dtor modeled on Rva0056B9A2::~Rva0056B9A2 (Code/GameEngine/Source/Common/Rva0056B9A2Dtor.cpp):
// vtable 0x00C766B8, AsciiString at +4 via base Rva003FCE38, notify rva002C004F
// with empty fallback g_Rva0107301CEmptyString, then base dtor 0x005C4B1B.
// Caller deleting dtor 0x005DB319. No donor name proven.
#include "ascii_string.h"

class Rva002D3627Host
{
public:
	void rva002C004F(const char *name);
};

extern Rva002D3627Host *g_00DFEF18;

__forceinline const char *GetStr005DB221(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class Rva003FCE38
{
public:
	virtual ~Rva003FCE38();
protected:
	AsciiString m_str;
};

class Rva005C4B1B : public Rva003FCE38
{
public:
	virtual ~Rva005C4B1B();
};

class Rva005DB221 : public Rva005C4B1B
{
public:
	virtual ~Rva005DB221();
};

Rva005DB221::~Rva005DB221()
{
	g_00DFEF18->rva002C004F(GetStr005DB221(m_str));
}
