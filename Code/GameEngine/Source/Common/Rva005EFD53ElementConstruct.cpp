// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??$_Construct@URva005EFD53Element@@U1@@_STL@@YAXPAURva005EFD53Element@@ABU1@@Z
// retail 0x005F09FF (24 B): STLport's _Construct placement-copying an element
// that holds a pointer to a reference-counted object (count at +0x08): null
// placement check, copy the pointer, bump the count when non-null. Callers:
// the element vector's push_back / _M_insert_overflow / fill_n bodies
// (StlportVectorPushBackFamily.cpp, StlportVectorInsertOverflowFamily.cpp,
// Rva005EF424FillN.cpp), which declare this specialization. Element and
// target names stay address-derived.
#include <memory>

#include "RegionIconSlotReferenceView.h"

namespace _STL
{
template <>
void _Construct<Rva005EFD53Element, Rva005EFD53Element>(Rva005EFD53Element *__p, const Rva005EFD53Element &__val)
{
	_STLP_PLACEMENT_NEW (__p) Rva005EFD53Element(__val);
}
}
