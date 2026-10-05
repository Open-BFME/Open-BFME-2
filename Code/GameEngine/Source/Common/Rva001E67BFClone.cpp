// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
//
// ?rva001E67BF@Rva001E4DB0@@QAE?AV1@XZ, retail 0x001E67BF, 94 bytes.
// By-value copy helper: makes a local Rva001E4DB0 from *this through the
// copy-constructor at 0x001E4DEB (same vtable 0x007DE8B4, base Rva001E3624
// and AsciiString at +0x10 as the rowed dtor 0x001E4DB0 proves), copies it
// to the hidden return slot, then destroys the local through the rowed
// dtor. Caller 0x004DA49E. Owner proven by vtable/base/callee layout.
#include "ascii_string.h"

class Rva001E3624
{
public:
	Rva001E3624(const Rva001E3624 &o);
	virtual ~Rva001E3624();
private:
	char m_pad04[0x0C];
};

class Rva001E4DB0 : public Rva001E3624
{
public:
	Rva001E4DB0(const Rva001E4DB0 &o);
	virtual ~Rva001E4DB0();
	Rva001E4DB0 rva001E67BF();
private:
	AsciiString m_10;
	char m_pad14[0x13C];
	bool m_150;
	char m_pad151[0x03];
};

Rva001E4DB0 Rva001E4DB0::rva001E67BF()
{
	Rva001E4DB0 tmp(*this);
	tmp.m_150 = false;
	return tmp;
}
