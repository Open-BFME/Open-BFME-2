// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// vector<UnicodeString>::~vector, retail 0x59F7C: same-shape sibling of the
// AsciiString instantiation at 0x2CC70 (StlportAsciiStringVectorDtor.cpp).
// It destroys the elements through _Destroy<UnicodeString*> at 0x56FC0
// (rowed in stlport_vector_unicode_reserve.cpp), then frees the storage.
#include <vector>

#include "unicode_string.h"


typedef char UnicodeStringExtent[sizeof(UnicodeString) == 4 ? 1 : -1];
template _STL::vector<UnicodeString>::~vector();
