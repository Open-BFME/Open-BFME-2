// ?rva001022F5@Rva001022F5@@QAEEABVAsciiString@@@Z
// partial score=0.95 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHs-c-
//
// ?rva001022F5@Rva001022F5@@QAEEABVAsciiString@@@Z @0x001022F5 42B.
// Clear via 0x0010223B then create LookupTablePostEffect via 0x00101FD8
// then null-checked 0x00116482 on result then return m_00 != 0.
// Evidence: packet disassembly call 0x10223B then push [esp+8] call 0x101FD8
// test mov je call 0x116482 cmp setne ret 4; callees all rowed;
// caller 0x000B0774 passes AsciiString temp; siblings 0x0010223B 0x0010225F same this+vector layout.
// Near miss: unsigned char return gives cmp [esi],0 exact; only retail mov ecx,esi before Create still missing (dead reload of this across stdcall).
#include "ascii_string.h"

class Rva0010223B
{
public:
	void rva0010223B();
};

class Rva00116482
{
public:
	void rva00116482();
};

class LookupTablePostEffect
{
public:
	char m_pad[12];
};

LookupTablePostEffect *__stdcall Rva00101FD8Create(const StringBase<char> &name);

class Rva001022F5
{
public:
	unsigned char rva001022F5(const AsciiString &arg);
private:
	Rva00116482 *m_00;
	char m_pad[12];
};

// ?rva001022F5@Rva001022F5@@QAEEABVAsciiString@@@Z present-unmatched
unsigned char Rva001022F5::rva001022F5(const AsciiString &arg)
{
	((Rva0010223B *)this)->rva0010223B();
	m_00 = (Rva00116482 *)Rva00101FD8Create((const StringBase<char> &)arg);
	if (m_00)
		m_00->rva00116482();
	return m_00 != 0;
}
