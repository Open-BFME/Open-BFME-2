// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Pristine STLport 4.5.3 vector members for placeholder POD elements, in the
// _STLP_USE_MALLOC allocator configuration. Each body was placed by a single
// masked whole-.text hit and its own bytes carry the element stride.
// BfmePodN stands for the real N-byte element at each site; where retail's
// copy construct for it is non-trivial, _Construct<BfmePodN> is pinned by
// call-site address, not compiled here. No retail caller is claimed. The
// 8/12/16-byte callees resolve to the existing BfmeE8/E12/E16 rows, the same
// placeholder sizes under their older names.
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
struct BfmePod8 { int a[2]; };
struct BfmePod12 { int a[3]; };
struct BfmePod16 { int a[4]; };
struct BfmePod40 { int a[10]; };
struct BfmePod44 { int a[11]; };
struct BfmePod68 { int a[17]; };
template class _STL::vector<BfmePod8, _STL::allocator<BfmePod8 > >;
template class _STL::vector<BfmePod12, _STL::allocator<BfmePod12 > >;
template class _STL::vector<BfmePod16, _STL::allocator<BfmePod16 > >;
template class _STL::vector<BfmePod40, _STL::allocator<BfmePod40 > >;
template class _STL::vector<BfmePod44, _STL::allocator<BfmePod44 > >;
template class _STL::vector<BfmePod68, _STL::allocator<BfmePod68 > >;

// MilesAudioManager's 8-byte trigger-area records: retail folds their erase
// onto the BfmePod8 body (0x003FA4DB, called twice by 0x000587C6).
struct AudioTriggerArea { int a[2]; };
struct AudioTriggerAreaSave { int a[2]; };
template AudioTriggerArea *_STL::vector<AudioTriggerArea, _STL::allocator<AudioTriggerArea > >::erase(AudioTriggerArea *, AudioTriggerArea *);
template AudioTriggerAreaSave *_STL::vector<AudioTriggerAreaSave, _STL::allocator<AudioTriggerAreaSave > >::erase(AudioTriggerAreaSave *, AudioTriggerAreaSave *);
