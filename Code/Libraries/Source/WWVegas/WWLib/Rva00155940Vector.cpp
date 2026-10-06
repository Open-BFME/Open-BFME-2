// cl: /Ireference/shims/bfmevector /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// Retail scalar deleting destructor at RVA 0x00155940, 71 bytes.
// Target facts: vtable VA 0x00BD3B98 points back to this destructor and to
// Resize 0x001A3720, whose element stride is four bytes. The destructor
// releases the array at +4 only when the ownership byte at +0xD is set,
// clears the array/count/ownership fields, and honors the deleting flag.
// The WWLib VectorClass template supplies the matching implementation.
// Its element's application identity is unknown: this is not evidence for
// the 20-byte HLodClass::ModelNodeClass used by an earlier candidate.

void __cdecl operator delete[](void *) throw();
#include "vector.h"

class Rva00155940Element;
template class VectorClass<Rva00155940Element *>;
