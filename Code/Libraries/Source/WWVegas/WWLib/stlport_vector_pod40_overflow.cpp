// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@UBfmePod40@@V?$allocator@UBfmePod40@@@_STL@@@_STL@@IAEXPAUBfmePod40@@ABU3@ABU__false_type@2@I_N@Z,
// retail 0x00565B7D, 183 bytes. Dedicated TU.
//
// STLport 4.5.3 vector<BfmePod40>::_M_insert_overflow, the growth path of the
// push_back matched in stlport_pod_vector_bodies.cpp. Like the AnimSet
// precedent (Code/GameEngine/Source/GameLogic/Object/
// ObjectCreationList_AnimSetInsertOverflow.cpp, same 183B shape), /G7 emits
// the imul and the retail homing where the default blend keeps the lea form.
// The element carries a virtual dtor (vptr + 9 ints = 40B) so _M_clear stays
// a 30-byte out-of-line call to the rowed tidy at 0x005659E8; a trivial dtor
// inlines the free and gains 6B. _Construct is declared, not defined, so the
// copies call the pinned body at 0x0052C320. Explicit member (not
// whole-class) instantiation keeps the other members owned by the existing
// pod TUs.
//
// BfmePod40 names only the 40-byte element size, not an application type.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// These elements copy through real copy constructors; their _Construct
// bodies are rowed under the real element names, so call those.
struct BfmePod40;
class Rva0052BD59;
namespace _STL {
template <> void _Construct<Rva0052BD59, Rva0052BD59>(Rva0052BD59 *, const Rva0052BD59 &);
// 0x0052C320
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod40, BfmePod40>(BfmePod40 *p, const BfmePod40 &v)
{ _Construct((Rva0052BD59 *)p, (const Rva0052BD59 &)v); }
}
// _M_clear's range destroy is retail's rowed Rva0052C266DestroyRange
// (0x0052C266, Rva0052BF33DestroyTagged.cpp); forward to it so this TU's
// _M_clear copy calls its owner rather than an unaddressed _Destroy<BfmePod40*>.
struct BfmePod40;
struct Rva0052BF4DElem;
void __cdecl Rva0052C266DestroyRange(Rva0052BF4DElem *, Rva0052BF4DElem *);
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<BfmePod40 *>(BfmePod40 *__first, BfmePod40 *__last)
{ Rva0052C266DestroyRange(reinterpret_cast<Rva0052BF4DElem *>(__first), reinterpret_cast<Rva0052BF4DElem *>(__last)); } }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAUBfmePod40@@@_STL@@YAXPAUBfmePod40@@0ABU__false_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod40;
namespace _STL { template <> void __destroy_aux<BfmePod40 *>(BfmePod40 *,BfmePod40 *,__false_type const &); }

struct BfmePod40
{
	virtual ~BfmePod40();
	int a[9];
};
inline bool operator==(const BfmePod40 &x, const BfmePod40 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod40 &x, const BfmePod40 &y) { return x.a[0] < y.a[0]; }

namespace _STL
{
template <> void _Construct<BfmePod40, BfmePod40>(BfmePod40 *, const BfmePod40 &);
}

template void _STL::vector<BfmePod40>::_M_insert_overflow(
	BfmePod40 *,
	const BfmePod40 &,
	const _STL::__false_type &,
	unsigned int,
	bool);
