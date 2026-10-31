// cl: /O1 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// ??0Rva0002C4FD@@QAE@ABV?$StringBase@D@@0@Z @0x0002C4FD 57B
// Honest placeholder ctor: two StringBase<char> at +0 and +4 via pinned
// 0x000365F0 copy, returns this. Layout read from retail stores (copy to
// esi then lea ecx esi+4). Callers construct pair at 0x002086C5 et al and
// destroy via pair dtor 0x0002C0C0. Same 57B shape as pair two-arg ctor
// 0x002027B1 which already claims the STL name, so honest Rva name used.

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
#include "ascii_string.h"

// Teardown resolves to the verified 133-byte releaseBuffer worker at RVA 0x36410.
struct Rva0002C4FD
{
	AsciiString m_a; // +0
	AsciiString m_b; // +4
	Rva0002C4FD(const StringBase<char> &lhs, const StringBase<char> &rhs);
};

Rva0002C4FD::Rva0002C4FD(const StringBase<char> &lhs, const StringBase<char> &rhs)
	: m_a(*(const AsciiString *)&lhs), m_b(*(const AsciiString *)&rhs)
{
}
