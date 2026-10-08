// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?rva0056EE5F@Rva0056EE5F@@QAEEXZ retail 0x0056EE5F 121B
// Evidence: GetStringFromRegistry 0x00234E0B with Registered and empty via 0x00037BA0; compareNoCase true via 0x00037980; releaseBuffer 0x00036410; callers 0x00571C81 0x00571C93; precedent RegistryAsciiPath
typedef unsigned char Bool8;
class AsciiString;
#include "ascii_string.h"
bool __cdecl GetStringFromRegistry(AsciiString path, AsciiString key, AsciiString &val);
struct Rva0056EE5F
{
	Bool8 rva0056EE5F();
};
Bool8 Rva0056EE5F::rva0056EE5F()
{
	AsciiString val;
	GetStringFromRegistry("", "Registered", val);
	return (Bool8)(((const StringBase<char> &)val).compareNoCase("true") == 0);
}

// 0x00571C60: target bytes conditionally call two address-derived helpers
// using this, then compare the matched 0x0056EE5F result with the byte at
// +0xD2. Offsets and call relationships are target evidence; field meanings
// and the containing class identity remain unknown.
class AptOnlineLogin
{
public:
	void rva00571B75();
};
class Rva005706D4Call
{
public:
	void rva005706D4();
};
class Rva00571C60
{
public:
	void rva00571C60();

private:
	char m_pad00[0xC5];
	Bool8 m_c5;
	char m_padC6[0x0C];
	Bool8 m_d2;
};
void Rva00571C60::rva00571C60()
{
	if (m_c5) {
		((AptOnlineLogin *)this)->rva00571B75();
		((Rva005706D4Call *)this)->rva005706D4();
	}
	Bool8 *cached = &m_d2;
	Bool8 value = ((Rva0056EE5F *)this)->rva0056EE5F();
	if (*cached != value) {
		((Rva005706D4Call *)this)->rva005706D4();
		value = ((Rva0056EE5F *)this)->rva0056EE5F();
		*cached = value;
	}
}
