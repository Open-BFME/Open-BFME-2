// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0056D3FD@@UAE@XZ @0x0056D3FD 59B
// Opaque dtor called by the rowed ??_G 0x0056D61F (vtable 0x00C6DAA4#0).
// Same shape as the rowed ??1Rva00539926 (Rva005396E6Dtor.cpp): store own
// vtable 0x00C6DAA4, release the member at +0x08 through the rowed
// ?rva0056D3E3@Rva0056D3E3 0x0056D3E3 (its sole caller) under EH state 0, then
// call the out-of-line base dtor pinned as ??1Rva00539926Base at 0x004E84A4
// (resets to 0x00BC6F20). Identity unproven; address-derived names.

#include "ascii_string.h"
#include "unicode_string.h"

class __declspec(novtable) Rva00539926Base
{
public:
	Rva00539926Base() : m_04(0) {}
	virtual ~Rva00539926Base();
private:
	int m_04; // Refcount belongs to the base, as in the matched help sibling.
};

class Rva0056D3FD;
class InGameCommandButtonHelp {public: class Impl;};
class InGameCommandButtonHelp::Impl
{
public:
 Impl(Rva0056D3FD *owner, const UnicodeString &a,
  const UnicodeString &b, const UnicodeString &c, const UnicodeString &d,
  const AsciiString &e);
private:
 char m_data[0x38]; // Native allocation56B; provider defines the complete view.
};

class Rva0056D3E3
{
public:
	Rva0056D3E3(InGameCommandButtonHelp::Impl *value) : m_00(value) {}
	void rva0056D3E3();

private:
	void *m_00;
};

class Rva0056D3FD : public Rva00539926Base
{
public:
	Rva0056D3FD(const UnicodeString &a, const UnicodeString &b,
		const UnicodeString &c, const UnicodeString &d, const AsciiString &e);
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
// references, then its pointer is stored at +8. The recovered389B provider
// proves four UnicodeString inputs followed by an AsciiString image suffix.
// The former all-narrow prototype was a4B consumed view; callers now use
// the proper wide types. The opaque outer owner name is retained.
Rva0056D3FD::Rva0056D3FD(const UnicodeString &a, const UnicodeString &b,
	const UnicodeString &c, const UnicodeString &d, const AsciiString &e)
	: m_08(new InGameCommandButtonHelp::Impl(this, a, b, c, d, e))
{
}
