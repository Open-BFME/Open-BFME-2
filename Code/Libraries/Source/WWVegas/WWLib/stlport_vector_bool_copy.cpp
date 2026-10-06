// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport4.5.3 bit-vector copy used by CreateAHeroData at+0x5C.
// Retail stores two pointer/bit-offset iterators and an end-of-storage pointer.
// Direct helper calls and the bit-count arithmetic establish the specialization.
#include <vector>
template _STL::vector<bool>::vector(const _STL::vector<bool>&);
