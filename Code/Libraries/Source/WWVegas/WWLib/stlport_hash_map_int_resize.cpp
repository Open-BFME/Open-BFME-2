// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable
// stlport
//
// Dedicated TU for hashtable<int,int>::resize. The shared hash_map_int
// unit is built with /EHsc and emits an EH prologue retail does not have.

#include <hash_map>

template class _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, int> > >;
