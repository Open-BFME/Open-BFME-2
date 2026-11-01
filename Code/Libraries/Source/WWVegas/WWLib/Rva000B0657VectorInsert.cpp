// cl: /O1 /G7 /MD /EHsc
// stlport
// Reference: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d,
// inputs/vendor/stlport/stl/_vector.h: vector::insert(iterator,size_type,const T&).
// The complete native five-byte entry at RVA 0x000B0657 tail-calls the
// independently rowed same-instantiation _M_fill_insert at 0x000B0478.
// This ABI-only template view needs no vector layout or element fields;
// retain the existing element identity, which is address-derived where named so.
#include <vector>
struct BfmePod36;
namespace _STL {
template <> void vector<BfmePod36, allocator<BfmePod36> >::_M_fill_insert(BfmePod36 *, unsigned, const BfmePod36 &);
}
template void _STL::vector<BfmePod36,_STL::allocator<BfmePod36> >::insert(BfmePod36*,unsigned,const BfmePod36&);
