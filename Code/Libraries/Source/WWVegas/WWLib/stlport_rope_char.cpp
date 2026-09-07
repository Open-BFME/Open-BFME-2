// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <rope>

template class _STL::rope<char, _STL::allocator<char> >;

// _S_ref is unplaced: the former RVA 0x006C5300 candidate calls GlobalFree,
// not InterlockedIncrement. Its masked DIR32 match did not establish identity.
