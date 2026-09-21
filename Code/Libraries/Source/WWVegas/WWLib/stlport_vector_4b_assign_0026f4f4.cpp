// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector::operator= for a 4-byte POD element, retail 0x0026F4F4
// (163 bytes), rowed as ?dup_0026f4f4. The body is folded across 4-byte-POD
// vectors: 27 image-wide callers and none with a proven element type, so no
// single T is claimed. int is the spelling compiled here; any 4-byte POD
// instantiation emits the same bytes.
#include <vector>
template class _STL::vector<int, _STL::allocator<int > >;
