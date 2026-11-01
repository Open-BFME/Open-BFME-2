// cl: /O1 /G7 /MD /EHsc
// stlport
// Reference: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d,
// inputs/vendor/stlport/stl/_vector.h: vector::insert(iterator,size_type,const T&).
// The complete native five-byte entry at RVA 0x000B0652 tail-calls the
// independently rowed same-instantiation _M_fill_insert at 0x000B0395.
// This ABI-only template view needs no vector layout or element fields;
// retain the existing element identity, which is address-derived where named so.
#include <vector>
struct BfmeE16;
namespace _STL {
template <> void vector<BfmeE16, allocator<BfmeE16> >::_M_fill_insert(BfmeE16 *, unsigned, const BfmeE16 &);
}
template void _STL::vector<BfmeE16,_STL::allocator<BfmeE16> >::insert(BfmeE16*,unsigned,const BfmeE16&);
