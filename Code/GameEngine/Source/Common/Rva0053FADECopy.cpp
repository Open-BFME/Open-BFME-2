// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD
//
// ??0Rva0053FADE@@QAE@ABV0@@Z @0x0053FADE 85B: user-written copy
// constructor of a polymorphic class (vtable 0x00C694DC) shared as the base
// copy of 0x00540845 and 0x00541F1F. Its non-polymorphic base at +4 (rowed
// Rva00330757Member default ctor 0x00330757) is default-constructed rather
// than copied (the vtable store follows it) and +0x14 is reset to zero; the
// AsciiString at +0x18 and the plain fields at +0x1C and +0x20 are copied.
// Identities are address-derived.

#include "ascii_string.h"

struct Rva00330757Member
{
	Rva00330757Member();
	~Rva00330757Member();

	char m_pad[0x10];
};

class Rva0053FADE : public Rva00330757Member
{
public:
	Rva0053FADE(const Rva0053FADE &other);
	virtual ~Rva0053FADE();

private:
	int m_14;
	AsciiString m_18;
	int m_1C;
	int m_20;
};

Rva0053FADE::Rva0053FADE(const Rva0053FADE &other) :
	m_14(0),
	m_18(other.m_18),
	m_1C(other.m_1C),
	m_20(other.m_20)
{
}
