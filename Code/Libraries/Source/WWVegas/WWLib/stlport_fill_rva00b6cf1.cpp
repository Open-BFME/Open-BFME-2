// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$fill@PAURva00B6CF1@@U1@@_STL@@YAXPAURva00B6CF1@@0ABU1@@Z @0x000B67F6 29B
// _STL::fill forward assign loop stride 8 via rowed operator= at 0x000B433E. Same 29B shape as AsciiString fill 0x000B4300.
// Evidence: call to rowed assign 0x000B433E with add esi 8 and cmp to last; callers at 0x000C22E1 0x000C2325.
#include <vector>

#include "ascii_string.h"

struct Rva00B6CF1
{
	Rva00B6CF1 &operator=(const Rva00B6CF1 &o);
	AsciiString m_s0;
	AsciiString m_s1;
};

template void _STL::fill<Rva00B6CF1 *, Rva00B6CF1>(Rva00B6CF1 *, Rva00B6CF1 *, const Rva00B6CF1 &);
