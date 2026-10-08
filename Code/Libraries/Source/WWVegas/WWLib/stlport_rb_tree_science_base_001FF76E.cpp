// cl: /DNDEBUG /MD /EHsc
//
// ??0?$_Rb_tree_base@U?$pair@$$CBW4ScienceType@@_N@_STL@@V?$allocator@U?$pair@$$CBW4ScienceType@@_N@_STL@@@2@@_STL@@QAE@ABV?$allocator@U?$pair@$$CBW4ScienceType@@_N@_STL@@@1@@Z @0x001FF76E 35B
// STLport _Rb_tree_base header-node ctor for ScienceStore map<ScienceType,bool>.
// Evidence: pin name; callees AllocProxy 0x0014F3C4 and pool 0x002EB448 at g_Va00DB9440;
// caller _Rb_tree ctor 0x001FF852; shape precedent Rva002F0C55Helper/Rva002F0C32Helper
// (proxy via rowed int ctor then pool pop to +0 returning this).
#include "../../../../GameEngine/Include/Common/Rva002E8548Pool.h"

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
template <class _K, class _V> struct pair
{
	_K first;
	_V second;
};
template <class _Value, class _Alloc> struct _Rb_tree_base
{
	_Rb_tree_base(const _Alloc &__a);
};
}

inline void *__cdecl operator new(unsigned int, void *__p)
{
	return __p;
}

enum ScienceType
{
	SCIENCE_INVALID = -1
};

typedef _STL::pair<const ScienceType, bool> SciencePair;
typedef _STL::allocator<SciencePair> ScienceAlloc;

_STL::_Rb_tree_base<SciencePair, ScienceAlloc>::_Rb_tree_base(const ScienceAlloc &__a)
{
	(void)__a;
	_STL::allocator<int> tmp;
	_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > *proxy =
		(_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > *)this;
	__assume(proxy != 0);
	new (proxy) _STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> >(tmp, 0);
	proxy->_M_data = (unsigned int)g_Va00DB9440.rva002EB448();
}
