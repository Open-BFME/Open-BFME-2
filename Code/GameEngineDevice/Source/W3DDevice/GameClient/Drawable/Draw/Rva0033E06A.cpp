// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva0033E06A@Rva0033E06A@@QAEXPAURva0033E06AArg@@@Z @0x0033E06A 22B push AsciiString into vector.
// Evidence: add eax 0x64 then push plus add ecx 0x33C then rowed-pinned
// vector AsciiString push_back; caller 0x002D1DE6 in FUN_006D1C01;
// prev Rva0033DCD1 and next vector ContainerRecord share STL flags.

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include "ascii_string.h"
#include <vector>

struct Rva0033E06AArg
{
	char m_pad[0x64];
	AsciiString m_str; // +0x64
};

struct Rva0033E06A
{
	char m_pad[0x33C];
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_vec; // +0x33C
	void rva0033E06A(Rva0033E06AArg *arg);
};

void Rva0033E06A::rva0033E06A(Rva0033E06AArg *arg)
{
	m_vec.push_back(arg->m_str);
}
