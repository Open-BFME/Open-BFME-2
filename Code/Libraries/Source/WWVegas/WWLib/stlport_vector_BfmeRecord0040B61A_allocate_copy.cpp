// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_M_allocate_and_copy@PBUBfmeRecord0040B61A@@@?$vector@UBfmeRecord0040B61A@@V?$allocator@UBfmeRecord0040B61A@@@_STL@@@_STL@@IAEPAUBfmeRecord0040B61A@@IPBU2@0@Z @ 0x0040B323 (45B). Vector allocate-and-copy for the 16-byte BfmeRecord.
// Evidence: retail calls allocate 0x002226BE plus uninitialized_copy 0x0040B2FD stride 0x10; caller 0x0040B64F in vector<BfmeRecord>::operator= 0x0040B61A; same 45B ebp-tag shape as 0x00064432 and 0x002CFBF4.
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

#include <vector>

#include "ascii_string.h"

struct BfmeRecord0040B61A
{
	BfmeRecord0040B61A();
	BfmeRecord0040B61A(const BfmeRecord0040B61A &src);
	BfmeRecord0040B61A &operator=(const BfmeRecord0040B61A &src);
	AsciiString m_str;
	int m_04;
	int m_08;
	int m_0C;
};

template class _STL::vector<BfmeRecord0040B61A, _STL::allocator<BfmeRecord0040B61A> >;
