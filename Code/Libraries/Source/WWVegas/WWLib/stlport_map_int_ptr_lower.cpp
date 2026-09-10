// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// Dedicated TU for map<unsigned,void*>::_M_lower_bound. Reloc named this
// address as the signed-int tree but retail uses jb not jl.

#include <map>

template class _STL::map<unsigned, void *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, void *> > >;

