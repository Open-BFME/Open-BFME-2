// cl: /DNDEBUG /MD /EHsc
//
// ?helper@Rva002F1CB3@@AAEPAV1@H@Z @0x002F0C55 35B.
// Leaf helper pinned as ?helper@Rva002F1CB3@@AAEXH@Z: builds the
// _STLP_alloc_proxy at +0 via rowed 0x0014F3C4 with (empty allocator, 0),
// pops a node via pool 0x002EB448 at g_Va00DBD4C8, stores to +0 and returns
// this. Caller 0x002F1CBA in Rva002F1C5FSelfLink.cpp. Return type is
// pointer (retail moves eax,esi); the pin spells void.
#include "../../Include/Common/Rva002E8548Pool.h"

namespace _STL
{
template <class _Tp> class allocator
{
};
template <class _P, class _T, class _A> class _STLP_alloc_proxy
{
public:
	_STLP_alloc_proxy(const _A &__a, _P __p);
	_P _M_data;
};
}

inline void *__cdecl operator new(unsigned int, void *__p)
{
	return __p;
}

class Rva002F1CB3
{
	Rva002F1CB3 *helper(int x);
};

Rva002F1CB3 *Rva002F1CB3::helper(int x)
{
	(void)x;
	_STL::allocator<int> tmp;
	_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > *proxy =
		(_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > *)this;
	__assume(proxy != 0);
	new (proxy) _STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> >(tmp, 0);
	proxy->_M_data = (unsigned int)g_Va00DBD4C8.rva002EB448();
	return this;
}
