// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 28-byte POD element.
// The allocator and the trivial-copy worker are both settled; the placeholder
// BfmePod28 names only the 28-byte stride, matching the pod-vector TU convention.
//
// ??$__lower_bound@PAUBfmePod28@@U1@U?$less@UBfmePod28@@@_STL@@H@_STL@@YAPAUBfmePod28@@PAU1@0ABU1@U?$less@UBfmePod28@@@0@PAH@Z @0x005413B0 (66B):
// __lower_bound over BfmePod28 pointers with default less<> on a[0]; idiv
// stride count plus halving loop. Caller 0x005414DA.
// Evidence: unlock lane, all callees rowed, unblocks 0x005414C2.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include <algorithm>
struct BfmePod28
{
	unsigned int slot;			// +0x00
	int bannerID;				// +0x04
	const void *typeEntry;		// +0x08, the type table's key/info pair
	int state;					// +0x0C
	int progress;				// +0x10
	int timer;					// +0x14
	bool pendingDelete;			// +0x18
	// The default less<> of __lower_bound 0x005413B0: signed, on the first word.
	__forceinline bool operator<(const BfmePod28 &o) const { return (int)slot < (int)o.slot; }
};
// bfme link decl-only BfmePod28
namespace _STL { template <> BfmePod28 * vector<BfmePod28, allocator<BfmePod28> >::erase(BfmePod28 *, BfmePod28 *); }
template void _STL::vector<BfmePod28>::clear();
template void _STL::vector<BfmePod28>::_M_insert_overflow(BfmePod28 *, const BfmePod28 &, const _STL::__false_type &, unsigned int, bool);
template BfmePod28 *_STL::__lower_bound<BfmePod28 *, BfmePod28, _STL::less<BfmePod28>, int>(BfmePod28 *, BfmePod28 *, const BfmePod28 &, _STL::less<BfmePod28>, int *);
