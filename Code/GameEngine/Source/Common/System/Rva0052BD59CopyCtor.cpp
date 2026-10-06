// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??0Rva0052BD59@@QAE@ABV0@@Z, retail 0x0052BD59, 141 bytes.
// Copy ctor for an address-named value type holding strings at +4/+8/+0xC/+0x18,
// dwords at +0x10/+0x14/+0x20/+0x24 and bytes at +0x1C/+0x1D with vtable
// 0x00861A70. Evidence: StringBase<char> copies via pinned 0x000365F0 with EH
// states 0 then 1 then 2, sole caller 0x0052C33C placement construct, unlocks
// 0x0052C320. Sibling of Rva0052BDE6/Rva0052BE33/Rva0052BEF0 copy ctors (same
// manual vtable recipe, no base: first string unprotected then states 0-2).
#include "ascii_string.h"


extern const void *const g_00861A70[];

class Rva0052BD59
{
public:
	Rva0052BD59(const Rva0052BD59 &other);

private:
	const void *m_vtable; // +0
	AsciiString m_str04; // +4
	AsciiString m_str08; // +8
	AsciiString m_str0C; // +0xC
	unsigned int m_10; // +0x10
	unsigned int m_14; // +0x14
	AsciiString m_str18; // +0x18
	unsigned char m_b1C; // +0x1C
	unsigned char m_b1D; // +0x1D
	unsigned int m_20; // +0x20
	unsigned int m_24; // +0x24
};

Rva0052BD59::Rva0052BD59(const Rva0052BD59 &other)
	: m_vtable(g_00861A70)
	, m_str04(other.m_str04)
	, m_str08(other.m_str08)
	, m_str0C(other.m_str0C)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_str18(other.m_str18)
	, m_b1C(other.m_b1C)
	, m_b1D(other.m_b1D)
	, m_20(other.m_20)
	, m_24(other.m_24)
{
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00861A70@@3QBQBXB=??_7Rva004E16D9Record@@6B@")
