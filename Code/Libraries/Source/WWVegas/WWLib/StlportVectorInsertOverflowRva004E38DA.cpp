// Target boundary 0x004E38DA/183 is STLport vector::_M_insert_overflow
// false_type: ?_M_insert_overflow@?$vector@UBfmePod88@@V?$allocator@UBfmePod88@@@_STL@@@_STL@@IAEXPAUBfmePod88@@ABU3@ABU__false_type@2@I_N@Z,
// pinned name. Chain lane: calls 0x004E2227 which this session landed, now
// every callee rowed or pinned. Caller is push_back at 0x004E3BCE.
// Retail advances 0x58-byte elements and delegates to target helpers
// allocate 0x0023D35B, uninitialized_copy 0x004E3733, _Construct 0x004E3706,
// uninitialized_fill_n 0x004E3759, destroy+free 0x004E2227.
//
// BfmePod88 is a size-only view (88-byte non-trivial emitter); the concrete
// identity is recorded only where independent evidence supports it.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// _M_clear's range destroy is retail's rowed Rva004E1FCCGet (0x004E1FCC);
// forward to it so this TU's _M_clear copy calls that owner rather than an
// unaddressed _Destroy<BfmePod88*>.
struct BfmePod88;
struct Rva004E1AD5Item;
void __cdecl Rva004E1FCCGet(Rva004E1AD5Item *, Rva004E1AD5Item *);
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<BfmePod88 *>(BfmePod88 *__first, BfmePod88 *__last)
{ Rva004E1FCCGet(reinterpret_cast<Rva004E1AD5Item *>(__first), reinterpret_cast<Rva004E1AD5Item *>(__last)); } }

struct BfmePod88
{
public:
	BfmePod88(const BfmePod88 &other);
	BfmePod88 &operator=(const BfmePod88 &);
	~BfmePod88();
	char m_body[88]; // +0x00
};

namespace _STL {
template <> void _Construct<BfmePod88, BfmePod88>(
	BfmePod88 *, const BfmePod88 &);
}

template void _STL::vector<BfmePod88>::_M_insert_overflow(
	BfmePod88 *, const BfmePod88 &,
	const _STL::__false_type &, unsigned int, bool);
