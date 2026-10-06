// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0Rva00573B23@@QAE@ABV0@@Z @0x00573AC8 91B: copy constructor of
// Rva00573B23 (layout from Rva00573B23Ctor.cpp). It copies the base through
// the rowed Rva0055B0CC copy 0x0055B182, installs vtable 0x00C6E270 (slot 0
// is the rowed ??_GRva00573B23 0x00573C60, slot 12 its xfer 0x00573A35; the
// 0x00C6E2A0 view named in other notes is the same table from slot 12 on),
// then copies the AsciiString at +0x2C, the Coord at +0x30 (spelled as three
// floats here; a struct copy emits movsd) and the float at +0x3C. Caller:
// the order-object copy 0x00573EB8.

#include "ascii_string.h"

class Rva0055B0CC
{
public:
	Rva0055B0CC(const Rva0055B0CC &other);
	virtual ~Rva0055B0CC();
private:
	char m_pad04[0x28];
};

class Rva00573B23 : public Rva0055B0CC
{
public:
	Rva00573B23(const Rva00573B23 &other);
	virtual ~Rva00573B23();
private:
	AsciiString m_2c;
	float m_30;
	float m_34;
	float m_38;
	float m_3c;
};

Rva00573B23::Rva00573B23(const Rva00573B23 &other) :
	Rva0055B0CC(other),
	m_2c(other.m_2c),
	m_30(other.m_30),
	m_34(other.m_34),
	m_38(other.m_38),
	m_3c(other.m_3c)
{
}
