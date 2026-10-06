// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00111D65@LookupTablePostEffect@@UAEXXZ, retail 0x00111D65, 53 bytes.
// Virtual slot 3 (offset 0xC) of vtable 0x007CFAC8 (class of
// ??0LookupTablePostEffect@@QAE@XZ in LookupTablePostEffectCtor.cpp).
// Guarded resource release: takes the DX8 device mutex, releases the
// ref-counted handle at +0x08 through the rowed helper 0x005F2577, then
// releases the mutex. Callees all rowed (Lock 0x0011F520, release
// 0x005F2577, Assert 0x00120F50). No callers. Honest address name: class
// plus slot are proven, method identity is not.

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class Rva005F2577Holder
{
public:
	void rva005F2577();
private:
	void *m_ptr;
};

class AsciiString;

#include "ascii_string.h"


class LookupTablePostEffect
{
public:
	virtual AsciiString rva00111BE9() const;
	virtual void s1();
	virtual void s2();
	virtual void rva00111D65();
	virtual void s4();
private:
	int m_04;
	Rva005F2577Holder m_08;
};

// ?rva00111BE9@LookupTablePostEffect@@UBE?AVAsciiString@@XZ, retail 0x00111BE9, 28 bytes.
// Virtual slot 0 (offset 0x0) of vtable 0x007CFAC8. Returns the AsciiString
// literal "LookupTablePostEffect" (0x00BCFADC) by value through the rowed
// StringBase<char> const-char ctor 0x00037BA0. No callers. Honest address
// name: class plus slot are proven, method identity is not.
AsciiString LookupTablePostEffect::rva00111BE9() const
{
	return AsciiString("LookupTablePostEffect");
}

void LookupTablePostEffect::rva00111D65()
{
	BFMEDX8DeviceLock lock;
	m_08.rva005F2577();
}
