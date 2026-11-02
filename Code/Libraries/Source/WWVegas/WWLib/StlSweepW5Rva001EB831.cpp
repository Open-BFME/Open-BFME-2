// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001EB831Element { char bytes[9];Rva001EB831Element();Rva001EB831Element(const Rva001EB831Element&);~Rva001EB831Element();Rva001EB831Element&operator=(const Rva001EB831Element&); bool operator<(const Rva001EB831Element&)const; bool operator==(const Rva001EB831Element&)const; };
// The element range copy is rowed with LinearCampaignCarryoverInsert.cpp;
// declare it so this unit calls that copy instead of emitting its own.
namespace _STL { template <> Rva001EB831Element *__copy_backward<Rva001EB831Element *, Rva001EB831Element *, int>(Rva001EB831Element *, Rva001EB831Element *, Rva001EB831Element *, const random_access_iterator_tag &, int *); }

// Instantiate the recovered operation and its required template dependencies.
template Rva001EB831Element * _STL::__copy_backward_ptrs<Rva001EB831Element *, Rva001EB831Element *>(Rva001EB831Element *, Rva001EB831Element *, Rva001EB831Element *, _STL::__false_type const &);

// Native 001EB831 forwards the CarryoverUnit range to loop 001EB262.
#include "../../../../GameEngine/Include/GameLogic/CarryoverUnit.h"
namespace _STL {
template <> CarryoverUnit *__copy_backward<CarryoverUnit *, CarryoverUnit *, int>(CarryoverUnit *, CarryoverUnit *, CarryoverUnit *, const random_access_iterator_tag &, int *);
}
template CarryoverUnit *_STL::__copy_backward_ptrs<CarryoverUnit *, CarryoverUnit *>(CarryoverUnit *, CarryoverUnit *, CarryoverUnit *, const _STL::__false_type &);
