// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??$_M_allocate_and_copy@PAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@?$vector@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@V?$allocator@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@2@@_STL@@IAEPAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@1@IPAV21@0@Z @0x001FFA2D 45B
// Chain lane: vector<FillSciVec>::_M_allocate_and_copy via allocator twin
// 0x00395928 (pinned) and rowed __uninitialized_copy 0x00339962. Caller
// 0x001FFDAA. Spelled after _Vector_base shape: start +0 finish +4 proxy +8.
// stlport
#include <vector>

enum ScienceType { SCIENCE_NONE = 0 };
typedef _STL::vector<ScienceType, _STL::allocator<ScienceType> > FillSciVec;

namespace _STL {
template <> FillSciVec *allocator<FillSciVec>::allocate(unsigned int n, const void *hint) const;
template <> FillSciVec *__uninitialized_copy<FillSciVec *, FillSciVec *>(FillSciVec *first, FillSciVec *last, FillSciVec *result, const __false_type &tag);

template <> template <>
FillSciVec *vector<FillSciVec, allocator<FillSciVec> >::_M_allocate_and_copy<FillSciVec *>(size_type n, FillSciVec *first, FillSciVec *last)
{
    FillSciVec *result = this->_M_end_of_storage.allocate(n);
    __false_type tag;
    __uninitialized_copy(first, last, result, tag);
    return result;
}
}
