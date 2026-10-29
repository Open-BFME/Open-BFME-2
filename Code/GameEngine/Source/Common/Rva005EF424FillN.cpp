// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
// ??$__uninitialized_fill_n@PAURva005EFD53Element@@IU1@@_STL@@YAPAURva005EFD53Element@@PAU1@IABU1@ABU__false_type@0@@Z @0x005EF424 (37B).
// _STL::__uninitialized_fill_n<Rva005EFD53Element>, retail 37 bytes. Dedicated TU
// so no local _Construct definition can inline into this loop. Element
// stride is 4 via the dummy body below; _Construct is declared only
// and resolves through the pin at 0x005F09FF. Unblocks 0x005EF4A5.
#include "RegionIconSlotReferenceView.h"

#include <memory>

// _Construct stays declared only, so the element copy remains an out-of-line call.
namespace _STL { template <> void _Construct<Rva005EFD53Element, Rva005EFD53Element>(Rva005EFD53Element *, const Rva005EFD53Element &); }

template Rva005EFD53Element *_STL::__uninitialized_fill_n(Rva005EFD53Element *, unsigned int, const Rva005EFD53Element &, const _STL::__false_type &);
