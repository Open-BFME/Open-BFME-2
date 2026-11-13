// cl: /DNDEBUG /MD /EHsc
//
// ??0?$_Rb_tree_base@HV?$Rva002F0C32Allocator@H@@@_STL@@QAE@ABV?$Rva002F0C32Allocator@H@@@Z @0x002F0C32 35B.
// The base constructor of the pool-allocated int multiset: builds the
// _STLP_alloc_proxy at +0 via rowed 0x0014F3C4 with (empty allocator, 0),
// pops the header node via pool 0x002EB448 at g_IntKeyedTreeNodePool and stores
// it at +0. Caller 0x002F1C66 in Rva002F1C5FSelfLink.cpp. AIPathfind.cpp declares
// this specialization and emits no copy of its own.
#include "../../Include/Common/Rva002EB448.h"

#include "../../Include/Common/Rva002E8548Pool.h"
extern Rva002E8548 g_IntKeyedTreeNodePool; // canonical24-byte pool owner in Rva007B6880Thunks.cpp

template <class T> class Rva002F0C32Allocator
{
};

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
template <class _Tp, class _Alloc> class _Rb_tree_base;
template <> class _Rb_tree_base<int, Rva002F0C32Allocator<int> >
{
public:
	typedef Rva002F0C32Allocator<int> allocator_type;
	_Rb_tree_base(const allocator_type &);
private:
	unsigned int _M_header;
};

_Rb_tree_base<int, Rva002F0C32Allocator<int> >::_Rb_tree_base(const allocator_type &)
{
	allocator<int> tmp;
	_STLP_alloc_proxy<unsigned int, int, allocator<int> > *proxy =
		(_STLP_alloc_proxy<unsigned int, int, allocator<int> > *)this;
	__assume(proxy != 0);
	typedef _STLP_alloc_proxy<unsigned int, int, allocator<int> > ProxyType;
	proxy->ProxyType::_STLP_alloc_proxy(tmp, 0);
	proxy->_M_data = (unsigned int)((Rva002EB448 *)&g_IntKeyedTreeNodePool)->rva002EB448();
}
}
