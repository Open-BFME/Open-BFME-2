// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// vector<UnicodeString>::~vector, retail 0x59F7C: same-shape sibling of the
// AsciiString instantiation at 0x2CC70 (StlportAsciiStringVectorDtor.cpp).
// It destroys the elements through _Destroy<UnicodeString*> at 0x56FC0
// (rowed in stlport_vector_unicode_reserve.cpp), then frees the storage.
// Use the same game allocator spelling as the kept shared UnicodeString
// container definitions in MilesAudioManager.cpp (retail free RVA 0x00030830).
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block); }
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releaseUnicodeStringStorage(void *storage)
{
	_STL::free(storage);
}
#include <vector>

#include "unicode_string.h"

namespace _STL {
template<> inline void allocator<UnicodeString>::deallocate(UnicodeString *__p, size_type) const
{
	if (__p != 0) releaseUnicodeStringStorage((void *)__p);
}
}


typedef char UnicodeStringExtent[sizeof(UnicodeString) == 4 ? 1 : -1];
template _STL::vector<UnicodeString>::~vector();
