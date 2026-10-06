// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??0Rva0052BE33@@QAE@ABV0@@Z, retail 0x0052BE33, 99 bytes.
// Copy ctor for an address-named value type holding strings at +4/+8/+0xC
// and a byte at +0x10 with vtable 0x00C61B78. Evidence: StringBase<char>
// copies via pinned 0x000365F0 from param+4/+8/+0xC to this+4/+8/+0xC with
// EH states 0 then 1 then 2, byte from param+0x10, sole caller 0x0052C3AE
// placement construct, unlocks 0x0052C392. Sibling of Rva0052BDE6 and
// Rva0052BEF0 copy ctors (same empty-base EH plus manual vtable recipe).
#include "ascii_string.h"


extern const void *const g_00C61B78[];

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class Rva0052BE33 : public EmptyBase
{
public:
	Rva0052BE33(const Rva0052BE33 &other);

private:
	const void *m_vtable; // +0
	AsciiString m_str04; // +4
	AsciiString m_str08; // +8
	AsciiString m_str0C; // +0xC
	unsigned char m_b10; // +0x10
};

Rva0052BE33::Rva0052BE33(const Rva0052BE33 &other)
	: m_vtable(g_00C61B78)
	, m_str04(other.m_str04)
	, m_str08(other.m_str08)
	, m_str0C(other.m_str0C)
	, m_b10(other.m_b10)
{
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00C61B78@@3QBQBXB=??_7Rva004E179A@@6B@")
