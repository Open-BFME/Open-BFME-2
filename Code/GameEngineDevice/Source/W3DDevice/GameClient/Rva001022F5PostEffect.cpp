// cl: /Ireference/shims/bfme2_ascii /MD /EHs-c-
//
// Target evidence: 0x001022F5 is a 42-byte Ghidra body. It clears state through 0x0010223B, calls the matched stdcall factory at 0x00101FD8 with one StringBase<char> stack argument, applies 0x00116482 to the returned object, and returns whether m_00 is non-null.
// The call-site view for 0x00101FD8 uses ECX=this to preserve the retail caller sequence; the matched factory reads its stack argument and does not use ECX. That view is a candidate ABI shape, not a claim about the factory identity.
// The target name and private field view remain address-derived; donor or old set/AsciiString labels are not asserted.
#include "ascii_string.h"

#include "../../../../GameEngine/Include/Common/Rva0010223B.h"

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

class Rva001022F5
{
public:
	unsigned char rva001022F5(const AsciiString &arg);
private:
	Rva00116482 *m_00;
	char m_pad[12];
};

// Native factory101FD8 ignores ambientECX and consumes one stack reference.
// The single established provider is stdcall; keep this caller's receiver.
LookupTablePostEffect *__stdcall Rva00101FD8Create(const StringBase<char> &);
union NativePostEffectFactoryCall {
 LookupTablePostEffect *(__stdcall *target)(const StringBase<char> &);
 LookupTablePostEffect *(Rva001022F5::*member)(const StringBase<char> &);
};
typedef char PostEffectFactoryPointerWidth[sizeof(NativePostEffectFactoryCall)==4 ? 1 : -1];

unsigned char Rva001022F5::rva001022F5(const AsciiString &asciiString)
{
	((Rva0010223B *)this)->rva0010223B();
	NativePostEffectFactoryCall factory={&Rva00101FD8Create};
	m_00 = (Rva00116482 *)(this->*factory.member)((const StringBase<char> &)asciiString);
	if (m_00)
		m_00->rva00116482();
	return m_00 != 0;
}
