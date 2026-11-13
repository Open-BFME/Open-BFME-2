// cl: /MD /EHsc /D_CRTIMP= /Ireference/shims/bfme2_ascii
// ??1Rva005DB221@@UAE@XZ @0x005DB221 80B
// dtor modeled on Rva0056B9A2::~Rva0056B9A2 (Code/GameEngine/Source/Common/Rva0056B9A2Dtor.cpp):
// vtable 0x00C766B8, AsciiString at +4 via base Rva003FCE38, notify rva002C004F
// with empty fallback g_Rva0107301CEmptyString, then base dtor 0x005C4B1B.
// Caller deleting dtor 0x005DB319. No donor name proven.
#include "ascii_string.h"

// LINK: rva002C004F's rowed home is Rva002BFF5A (Rva002C004FErase.cpp, 0x2C004F);
// the old Rva002D3627Host spelling named an unresolved symbol. The global keeps
// its pointer type, the call binds the rowed member through a cast.
class Rva002D3627Host;
#include "../../Include/Common/Rva002BFF5A.h"

class LivingWorld; extern LivingWorld *TheLivingWorld;

__forceinline const char *GetStr005DB221(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/Common/Rva003FCE38.h"

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
	((Rva002BFF5A *)((Rva002D3627Host *)TheLivingWorld))->rva002C004F(GetStr005DB221(m_str));
}
