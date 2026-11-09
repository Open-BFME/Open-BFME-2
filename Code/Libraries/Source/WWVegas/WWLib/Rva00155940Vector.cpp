// cl: /G7 /Ireference/shims/bfmevector /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// Retail scalar deleting destructor at RVA 0x00155940, 71 bytes.
// Target facts: vtable VA 0x00BD3B98 points back to this destructor and to
// Resize 0x001A3720, whose element stride is four bytes. The destructor
// releases the array at +4 only when the ownership byte at +0xD is set,
// clears the array/count/ownership fields, and honors the deleting flag.
// The WWLib VectorClass template supplies the matching implementation.
// Its element's application identity is unknown: this is not evidence for
// the 20-byte HLodClass::ModelNodeClass used by an earlier candidate.

#include <new>
#define _OPERATOR_NEW_DEFINED_
#include "vector.h"

class Rva00155940Element;
template class VectorClass<Rva00155940Element *>;

// Retail 0x00155360..0x001553BE is the complete RET8 constructor: the same
// base vtable 0x00BD3B98, four-byte storage, optional caller-owned array,
// derived vtable 0x00BD3BE8, zero active count and growth step ten.
// WWLib supplies the ordinary constructor; /G7 reproduces the two ADDs
// used to multiply the allocation count by four. The opaque pointer is
// this unit's existing representation, not a recovered application type.
template DynamicVectorClass<Rva00155940Element *>::DynamicVectorClass(
    unsigned, Rva00155940Element *const *);
