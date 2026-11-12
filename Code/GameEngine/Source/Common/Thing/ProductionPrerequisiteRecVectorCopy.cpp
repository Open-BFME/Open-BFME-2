// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Retail 0x002CFE45 copies 12-byte string-bearing records through
// 0x004F5097 -> 0x002CF99D -> 0x002CF5B1. Use that existing typed provider;
// the separate raw PrereqUnitRec push_back/overflow family is not this record.
// Its application identity remains unknown. Evidence and the exact EH graph:
// reverse/attempt_support/prereq-copy-provider-20261023-bce2/typed-reconciliation.md
#include <vector>
#include "ascii_string.h"

#include "../../../Include/Common/BfmeStringRecord002CF5B1.h"

namespace _STL {
template <> __declspec(noinline) inline BfmeStringRecord002CF5B1 *
__uninitialized_copy<const BfmeStringRecord002CF5B1 *, BfmeStringRecord002CF5B1 *>(
    const BfmeStringRecord002CF5B1 *first, const BfmeStringRecord002CF5B1 *last,
    BfmeStringRecord002CF5B1 *result, const __false_type &)
{
    BfmeStringRecord002CF5B1 *cur = result;
    for (; first != last; ++first, ++cur)
        _Construct(&*cur, *first);
    return cur;
}
}

// Retail has an EH frame here. The link keeps the independently verified
// no-EH const-copy worker from stlport_vector_stringrecord_2cf5b1_allocate_copy.
template _STL::vector<BfmeStringRecord002CF5B1>::vector(
    const _STL::vector<BfmeStringRecord002CF5B1> &);
