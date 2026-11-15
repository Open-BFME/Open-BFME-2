// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "../../../../GameEngine/Include/Common/Rva00541021.h"

#include <algorithm>
#include <memory>

// Retail's loop calls _Construct<Rva00541021> (0x0054105B, Rva00541021Construct.cpp),
// so the 28-byte element is that unit's Rva00541021 with its rowed copy 0x00541021.
// bfme link decl-only begin
namespace _STL { template <> void _Construct<Rva00541021, Rva00541021>(Rva00541021 *, Rva00541021 const &); }
// bfme link decl-only end

// Instantiate the recovered operation and its required template dependencies.
template Rva00541021 * _STL::__uninitialized_copy<Rva00541021 const *, Rva00541021 *>(Rva00541021 const *, Rva00541021 const *, Rva00541021 *, _STL::__false_type const &);
