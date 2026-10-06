// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@QAEPAPBVModuleData@@PAPBV3@ABQBV3@@Z
// @ 0x003B67B3 (126B): STLport vector<const ModuleData*> single-element insert.
// Donor vendor/stlport/stl/_vector.h insert inline for trivial T: computes
// n = pos-begin then fast path *finish=x when pos==end else constructs
// *finish from *(finish-1) and shifts via __copy_trivial_backward and stores
// x_copy at pos else overflows via _M_insert_overflow with true_type tag.
// Callees rowed 0x00620840 __copy_trivial_backward and 0x002DFCF6 ModuleData
// overflow. Callers at 0x003B7D3F 0x003EF858 0x004BFC62 0x005058B6 0x0056961E
// 0x005F37A1. ModuleDataList is std::vector<const ModuleData*> per
// reference/shims/modulefactory/Common/ModuleFactory.h.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("s", off)
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class ModuleData;
typedef const ModuleData *Elem;

template _STL::vector<Elem>::iterator _STL::vector<Elem>::insert(
    _STL::vector<Elem>::iterator,
    const Elem &);
