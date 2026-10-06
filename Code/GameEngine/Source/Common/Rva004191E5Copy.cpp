// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD
//
// ??0Rva004191E5@@QAE@ABU0@@Z @0x004191E5 73B: copy constructor of a record
// holding an AsciiString at +0, a 12-byte member copied by the unrowed copy
// constructor 0x00419035 (+4; address-derived pin; no destructor unwind state
// in retail) and a BfmeFixedStorage002CF0F0 at +0x10 (rowed copy 0x002CF0F0).
// Callers 0x00419254 and 0x0041928E; record identity not recovered.

#include "ascii_string.h"

class Rva00419035
{
public:
	Rva00419035(const Rva00419035 &other);

private:
	char m_pad[0xC];
};

class BfmeFixedStorage002CF0F0
{
public:
	BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &other);

private:
	char m_pad[0xC];
};

struct Rva004191E5
{
	Rva004191E5(const Rva004191E5 &other);

	AsciiString m_00;
	Rva00419035 m_04;
	BfmeFixedStorage002CF0F0 m_10;
};

Rva004191E5::Rva004191E5(const Rva004191E5 &other) :
	m_00(other.m_00),
	m_04(other.m_04),
	m_10(other.m_10)
{
}
