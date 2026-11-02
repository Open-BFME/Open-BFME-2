// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$_Construct@UBfmePod172@@U1@@_STL@@YAXPAUBfmePod172@@ABU1@@Z @0x001EB9E6 45B: placement copy of 172B element via rowed CarryoverUnit copy ctor 0x001EB79E. Callers in stlport_pod_vector_bodies.cpp (__uninitialized_copy/fill_n/push_back). Pin from REL32 at placed body.
#include <new>
#include <vector>
struct BfmePod172 { int a[43]; };
#include "../../../../GameEngine/Include/GameLogic/CarryoverUnit.h"
namespace _STL {
template <> inline void _Construct<BfmePod172, BfmePod172>(BfmePod172 *__p, const BfmePod172 &__val)
{
	new ((void *)__p) CarryoverUnit((const CarryoverUnit &)__val);
}
}

template void _STL::_Construct<BfmePod172, BfmePod172>(BfmePod172 *, const BfmePod172 &);

template void _STL::_Construct<CarryoverUnit, CarryoverUnit>(CarryoverUnit *, const CarryoverUnit &);
