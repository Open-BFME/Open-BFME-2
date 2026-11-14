// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00381C2DClear@@YAXI@Z, retail 0x00381C2D, 30 bytes.
// Clears BfmeStringRecord vector at g_00E022F8[idx] via rowed erase when
// idx<2 (imul 12 for 12-byte vector begin/end/capacity, /G7 keeps imul;
// plain /O1 strength-reduces to lea lea). Evidence: callers
// in FUN_009118f3/FUN_009a20a7 push index, unblocks 5 functions, gap between
// rowed _M_insert_overflow 0x00381B7B and push_back 0x00381C4B in sibling TU
// (same flags plus /G7).
#include "unicode_string.h"
#include <vector>
#include "BfmeStringRecord005DDD40.h"
namespace _STL {
template <> void _Construct<BfmeStringRecord005DDD40, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
// Calls use the separately verified 0x00381B1F range-erase specialization.
template <> BfmeStringRecord005DDD40 *vector<BfmeStringRecord005DDD40, allocator<BfmeStringRecord005DDD40> >::erase(BfmeStringRecord005DDD40 *, BfmeStringRecord005DDD40 *);
}
unsigned int g_chatHistoryVectors[6];
// Retail startup constructs two 12-byte vectors in this zero-filled storage.
#define g_00E022F8 ((_STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > *)g_chatHistoryVectors)

void __cdecl Rva00381C2DClear(unsigned int idx)
{
	if (idx >= 2)
		return;
	_STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > &vec = g_00E022F8[idx];
	vec.erase(vec.begin(), vec.end());
}
