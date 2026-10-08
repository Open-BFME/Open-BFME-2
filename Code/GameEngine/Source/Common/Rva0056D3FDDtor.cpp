// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0056D3FD@@UAE@XZ @0x0056D3FD 59B
// Opaque dtor called by the rowed ??_G 0x0056D61F (vtable 0x00C6DAA4#0).
// Same shape as the rowed ??1Rva00539926 (Rva005396E6Dtor.cpp): store own
// vtable 0x00C6DAA4, release the member at +0x08 through the rowed
// ?rva0056D3E3@Rva0056D3E3 0x0056D3E3 (its sole caller) under EH state 0, then
// call the out-of-line base dtor pinned as ??1Rva00539926Base at 0x004E84A4
// (resets to 0x00BC6F20). Identity unproven; address-derived names.

#include "ascii_string.h"

class __declspec(novtable) Rva00539926Base
{
public:
	Rva00539926Base() : m_04(0) {}
	virtual ~Rva00539926Base();
private:
	int m_04; // Refcount belongs to the base, as in the matched help sibling.
};

class Rva0056D3FD;
class Rva0056D438
{
public:
	Rva0056D438(Rva0056D3FD *owner, const AsciiString &a,
		const AsciiString &b, const AsciiString &c, const AsciiString &d,
		const AsciiString &e);
private:
	char m_data[0x38];
};

class Rva0056D3E3
{
public:
	Rva0056D3E3(Rva0056D438 *value) : m_00(value) {}
	void rva0056D3E3();

private:
	void *m_00;
};

class Rva0056D3FD : public Rva00539926Base
{
public:
	Rva0056D3FD(const AsciiString &a, const AsciiString &b,
		const AsciiString &c, const AsciiString &d, const AsciiString &e);
	virtual ~Rva0056D3FD();

private:
	Rva0056D3E3 m_08;
};

Rva0056D3FD::~Rva0056D3FD()
{
	m_08.rva0056D3E3();
}

// Target [56D5BD,56D61F)98B shares the rowed destructor's vtable and layout:
// count +4 starts zero; new 56-byte implementation receives this and five
// string references, then its pointer is stored at +8. Target 56D438 copies
// four AsciiStrings and queries the fifth; WB's named SetupDisplayStrings
// supports InGameCommandButtonHelp, while the existing opaque owner is kept.
Rva0056D3FD::Rva0056D3FD(const AsciiString &a, const AsciiString &b,
	const AsciiString &c, const AsciiString &d, const AsciiString &e)
	: m_08(new Rva0056D438(this, a, b, c, d, e))
{
}
