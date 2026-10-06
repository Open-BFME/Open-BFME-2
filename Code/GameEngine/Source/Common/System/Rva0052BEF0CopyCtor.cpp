// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??0Rva0052BEF0@@QAE@ABV0@@Z, retail 0x0052BEF0, 67 bytes.
// Copy ctor for an address-named value type holding a string at +4 and a
// byte at +8 with vtable 0x00C61DC4. Evidence: StringBase<char> copy via
// pinned 0x000365F0 from param+4 to this+4, byte from param+8, sole caller
// 0x0052C431 placement construct, unlocks 0x0052C431.
#include "ascii_string.h"


extern const void *const g_00C61DC4[];

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class Rva0052BEF0 : public EmptyBase
{
public:
	Rva0052BEF0(const Rva0052BEF0 &other);

private:
	const void *m_vtable; // +0
	AsciiString m_str; // +4
	unsigned char m_b; // +8
};

Rva0052BEF0::Rva0052BEF0(const Rva0052BEF0 &other)
	: m_vtable(g_00C61DC4)
	, m_str(other.m_str)
	, m_b(other.m_b)
{
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00C61DC4@@3QBQBXB=??_7Rva004E1B72@@6B@")
