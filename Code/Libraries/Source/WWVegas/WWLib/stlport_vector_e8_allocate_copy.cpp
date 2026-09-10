// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Dedicated no-EH instantiation of vector<BfmeE8>::_M_allocate_and_copy.
// stlport_vector_e8_o1.cpp uses /EHsc and emits an EH frame; retail is the
// 45-byte ebp+tag body twin of vector<AsciiString>::_M_allocate_and_copy.

#include <vector>
struct BfmeE8 { int a, b; };
template class _STL::vector<BfmeE8, _STL::allocator<BfmeE8 > >;
