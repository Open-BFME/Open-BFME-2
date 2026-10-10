// ??$_M_allocate_and_copy@PBU?$pair@HH@_STL@@@?$vector@U?$pair@HH@_STL@@V?$allocator@U?$pair@HH@_STL@@@2@@_STL@@IAEPAU?$pair@HH@1@IPBU21@0@Z
// partial score=1.0 date=2026-10-10
// cl: /O2 /G6 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include <utility>
typedef _STL::pair<int,int> Pair;
template<>
template<>
Pair * _STL::vector<Pair, _STL::allocator<Pair> >::_M_allocate_and_copy<const Pair *>(
	unsigned int n, const Pair *first, const Pair *last)
{
	Pair *result = this->_M_end_of_storage.allocate(n);
	for (const Pair *p = first; p != last; ++p)
	{
		Pair *dest = (Pair *)((char *)result + ((char *)p - (char *)first));
		if (dest)
			*dest = *p;
	}
	return result;
}


