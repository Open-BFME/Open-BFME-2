// cl: /DNDEBUG /MD /EHsc
//
// ?helper@Rva002F1C5F@@AAEPAV1@H@Z @0x002F0C32 35B.
// Leaf helper pinned as ?helper@Rva002F1C5F@@AAEXH@Z: builds the
// _STLP_alloc_proxy at +0 via rowed 0x0014F3C4 with (empty allocator, 0),
// pops a node via pool 0x002EB448 at g_00DBD4B0, stores to +0 and returns
// this. Caller 0x002F1C66 in Rva002F1C5FSelfLink.cpp. Return type is
// pointer (retail moves eax,esi); the pin spells void.
class Rva002EB448
{
public:
	void *rva002EB448();
};

extern unsigned int g_Va00DBD4B0;	// pool object at 0x00DBD4B0 (Rva007B6880Thunks.cpp)

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

class Rva002F1C5F
{
	Rva002F1C5F *helper(int x);
};

Rva002F1C5F *Rva002F1C5F::helper(int x)
{
	(void)x;
	_STL::allocator<int> tmp;
	_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > *proxy =
		(_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > *)this;
	__assume(proxy != 0);
	new (proxy) _STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> >(tmp, 0);
	proxy->_M_data = (unsigned int)((Rva002EB448 *)&g_Va00DBD4B0)->rva002EB448();
	return this;
}
